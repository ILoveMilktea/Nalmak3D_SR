#include "stdafx.h"
#include "..\Include\Enemy.h"

#include "Bullet_Manager.h"


Enemy::Enemy(Desc * _Desc)
{
	m_fMaxSpd = _Desc->fMaxSpd;
	m_fLookSpd = _Desc->fLookSpd;
	m_fFov = _Desc->fFov;

	m_fFpm = _Desc->fFpm;
	m_iFullRound = _Desc->iRound;
	m_iCurRound = m_iFullRound;
	
	m_fFpm_Missile = _Desc->fFpm_Missile;
	m_iFullRound_Missile = _Desc->iRound_Missile;
	m_iCurRound_Missile = m_iFullRound_Missile;
	m_fFpmDelta_Missile = 60.f / m_fFpm_Missile;
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	Target_Setting(true);
	Target_Update();

	m_vOriginForward = m_transform->GetForward();
}

void Enemy::Update()
{	

	Target_Update();
	// Kiting();
	 Chase();
	// Drop();
	// Hold();

	//Dive();

	Reloading();

	//Decelerate();
	//Accelerate();

	
	//if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_RIGHT_ARROW))
	//{
	//	Quaternion qTemp = m_transform->RotateAxis(m_transform->GetUp(), -dTime*10.f);
	//	m_transform->rotation *= qTemp;
	//}
	//if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_ARROW))
	//{
	//	Quaternion qTemp = m_transform->RotateAxis(m_transform->GetUp(), dTime*10.f);
	//	m_transform->rotation *= qTemp;
	//}
#pragma region DebugLog
	//DEBUG_LOG(L"Target On?", bTarget);
	DEBUG_LOG(L"타겟 까지의 거리", m_fDist_Target);
	DEBUG_LOG(L"타겟과의 내적 값", m_fInner);
	//DEBUG_LOG(L"UpVector과의 내적 값", m_fUpInner);
	//DEBUG_LOG(L"Up Angle", m_fUpAngle);
	DEBUG_LOG(L"Player is in the Enemy Fov", m_bFov);
	DEBUG_LOG(L"Enemy Current Speed", m_fSpd);
	DEBUG_LOG(L"Remain Round", m_iCurRound);


#pragma endregion
}


void Enemy::Target_Setting(bool _onoff)
 {	
	if (_onoff == true)
	{
		m_pTarget = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);

		if (m_pTarget)
		{
			/* First Inner Setting */
			Vector3 vDir = m_pTarget->GetTransform()->position - m_transform->position;
			D3DXVec3Normalize(&vDir, &vDir);
			
			m_fInner_First = D3DXVec3Dot(&vDir, &m_transform->GetForward());

			bTarget = true;
			return;
		}

		
	}
	else 
	{
		m_pTarget = nullptr;
		bTarget = false;
	}

}

void Enemy::Target_Update()
{
	if (bTarget) 
	{
		/* Dot calc to Target Direction Vector */
		/* for distance, fInner */
		Vector3 vDir = m_pTarget->GetTransform()->position - m_transform->position;
		m_fDist_Target = D3DXVec3Length(&vDir);
		D3DXVec3Normalize(&vDir, &vDir);

		m_fInner = D3DXVec3Dot(&vDir, &m_transform->GetForward());

		/* Dot calc to Target Up Vector */
		/* for horizontally */
		Vector3 Flight = { 0.f, 0.f, 0.f };
		D3DXVec3Normalize(&Flight, &m_transform->GetRight());

		Vector3 World = { 0.f, 1.f, 0.f };
		m_fUpInner = D3DXVec3Dot(&Flight, &World);
		m_fUpAngle = D3DXToDegree(acosf(m_fUpInner));
	}

}


void Enemy::Go_ToPos(Vector3 _pos)
{
	m_transform->LookAt(_pos, m_fLookSpd, &m_QuartRot);
	m_transform->position += m_transform->GetForward() * m_fSpd * dTime;
}

void Enemy::Go_Straight()
{
	m_transform->position += m_transform->GetForward() * m_fSpd * dTime;
}

void Enemy::Look_Target()
{
	if (bTarget)
	{
		m_transform->LookAt(m_pTarget, m_fLookSpd, &m_QuartRot);
	}
}

bool Enemy::Fov_Check()
{
	if (D3DXToRadian(m_fFov/2.f) >= acosf(m_fInner))
	{
		m_bFov = true;
		return true; 
	}
	else 
	{ 
		m_bFov = false; 
		return false;
	}
}

void Enemy::Damaged(const int & _playerDmg)
{
}

const int & Enemy::Get_Damage()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_iAtt;
}

const int & Enemy::Get_FullHp()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_iFullHp;
}

const int & Enemy::Get_CurHp()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_iCurHp;
}

void Enemy::Set_Damage(const int & _dmg)
{
}

//린 쓰지말고 걍 내적 0이면 수평 맞추는 것만 해보자.
void Enemy::Lean()
{
#pragma region Failed
	//if (!bTarget)
	//{
	//	return;
	//}
	///* angle? 현재 위치에서 타겟 위치의 사이 각도?*/
	///* or 저번 각도와 현재 각도의 차이?*/
	///* 타겟과의 거리 벡터와 나의 직진벡터 내적으로 각도 구하고*/

	//m_fTurnDeltaTime += dTime;

	//if (m_fTurnDeltaTime >= m_fTurnUpdateTime)
	//{
	//	Vector3 vDir = m_Target->GetTransform()->position - m_transform->position;
	//	D3DXVec3Normalize(&vDir, &vDir);

	//	/* fInner -> 내적의 결과값, cos세타 임. */
	//	/*float */m_fInner = D3DXVec3Dot(&vDir, &m_transform->GetForward());
	//	/*DEBUG_LOG(L"Inner 값", fInner);*/
	//	/* ㄹㅇ 각도를 구하기 위해서는 역코사인 ㄱㄱ */
	//	/* 라디안 값으로 나옴. */
	//	float fRad = acosf(m_fInner);
	//	float fDegree = D3DXToDegree(fRad);

	//	/* 내적 특징 -> 결과값 범위 -1 ~ 0 ~ 1 */
	//		/* 내적값이 -1에 가깝다 : 바라보고 있는 반대편 방향과 수평에 가깝다. */
	//		/* 내적값이 0에 가깝다  : 타겟과 수직에 가깝다. */
	//		/* 내적값이 1에 가깝다  : 바라보고 있는 방향과 수평에 가깝다. */
	//		/* 기체 최대 기울어짐 각도 : -50 ~ 0 ~ 50 */

	//	/* 타겟이 오른쪽에 있을 경우에서 */
	//	//내적값 0 ~ 0.5 까지는 기울기 증가 -> 
	//	//내적값 0.5 ~ 1 에서는 기울기 감소 -> 1에 가까워지면 수평이 되게.

	//	//if (fInner >= 0.f && fInner <= 0.5f)
	//	//{
	//	//	fTemp = (-50 * fInner + 50) * -dTime;
	//	//	//fTemp = fInner * -dTime;
	//	//}
	//	//else if (fInner > 0.5f && fInner <= 0.9f)
	//	//{
	//	//	fTemp = (-50 * fInner + 50) * dTime;
	//	//	//fTemp = fInner * dTime;
	//	//	//fTemp = Nalmak_Math::Lerp(fTemp,0.f,dTime);
	//	//}

	//	/*
	//	ㄴㄴㄴㄴ지금 0 ~ 0.5 0.5 ~ 1 처럼 주면 시작지점에서의 각도가 90도 이상이여야함.
	//	그렇게 말고
	//	처음 딱 타겟 잡았을 때(SetTarget) 시작 Inner 값과
	//	타겟에 도착했을때 Inner값을 백분률로 나눠서 조건을 걸어줘야
	//	맞지 않겠냐 이거야.
	//		=> 나중에 플레이어를 타겟으로 잡을때에는 플레이어 이동마다 계산해줘야 할듯?
	//	*/
	//	if (m_fInner >= m_fInner_First && m_fInner <= (m_fInner_First+ m_fInner_Goal)/2.f)
	//	{ //기울어 지는 곳
	//		m_fTurnRotZ = (-50 * m_fInner + 50) * dTime * m_fTurnSpd;

	//		Quaternion qTemp = m_transform->RotateAxis(m_transform->GetForward(), -m_fTurnRotZ);
	//		m_transform->rotation *= qTemp;
	//	}
	//	if (m_fInner >(m_fInner_First + m_fInner_Goal) / 2.f && m_fInner <= 0.9f)
	//	{ //수평으로 돌아 오는 곳
	//		m_fTurnRotZ = (-50 * m_fInner + 50) * dTime * m_fTurnSpd;

	//		Quaternion qTemp = m_transform->RotateAxis(m_transform->GetForward(), m_fTurnRotZ);
	//		m_transform->rotation *= qTemp;
	//	}

	//	//지금 반대편에 있어서 음수가 나오면 혼자 회전하고 지123랄남
	//	//내적 음수 나오면 
	//	
	//	

	//	/* 타겟과의 각도가 좁아지면 1과 가까워짐, 90도에 가까워지면 0*/
	//	/* 각도가 좁아지면 0, 멀어지면 50 */
	//	/* 1일때 0, 0일때 50.f*/

	//	//fRotZ = 0.f;
	//	//fRotZ = -50 * fInner + 50;
	//	//DEBUG_LOG(L"fRotZ 값", fRotZ);

	//	//m_QuartRot *= temp;

	//	/*확인용*/
	//	//float fTemp;
	//	//fTemp = 0.f;

	//	//if(fInner >= 0.95)
	//	//fTemp = (-50 * fInner + 50) * -dTime;
	//	
	//	//DEBUG_LOG(L"Temp fRotZ 값", fTemp);
	//	

	//	m_fTurnDeltaTime = 0.f;
	//}
#pragma endregion
}

void Enemy::Horizontally()
{
	//Player Axis is not always alinged to World Y axis
	//therefore, need modify. alinged to Player Y axis.
	
	if (m_fInner >= 0.99f)
	{
		if (m_fUpAngle < 89.f)
		{
			Quaternion qTemp = m_transform->RotateAxis(m_transform->GetForward(), -dTime);
			m_transform->rotation *= qTemp;
		}
		if (m_fUpAngle > 89.f)
		{
			Quaternion qTemp = m_transform->RotateAxis(m_transform->GetForward(), dTime);
			m_transform->rotation *= qTemp;
		}
	}
	if (m_fInner < 0.f)
	{

	}
}

void Enemy::Turn()
{

}

bool Enemy::Dive()
{
	Target_Setting(false);
	
	Quaternion Xaxis = m_transform->RotateAxis(m_transform->GetRight(), dTime);
	m_transform->rotation *= Xaxis;

	// 다이브,소어 둘 다 시작 할때 원래 forward값 받아 놨다가 
	// 그 값이랑 비교해서 수직이 될때까지 몸체 돌기
	Vector3 Z = m_transform->GetForward();
	//Vector3 WorldY = { 0.f,1.f,0.f };

	m_fDiveInner = D3DXVec3Dot(&Z, &m_vOriginForward);

	if (m_fDiveInner <= 0.1f && m_fDiveInner >= -0.1f) //범위 0에 가까우면
	{
		return true;
	}

	DEBUG_LOG(L"다이브 Inner", m_fDiveInner);
	Go_Straight();
	
	return false;
}

bool Enemy::Soar()
{
	Target_Setting(false);

	Quaternion Xaxis = m_transform->RotateAxis(m_transform->GetRight(), -dTime);
	m_transform->rotation *= Xaxis;

	Vector3 Z = m_transform->GetForward();
	//Vector3 WorldY = { 0.f,1.f,0.f };

	m_fSoarInner = D3DXVec3Dot(&Z, &m_vOriginForward);

	if (m_fSoarInner <= 0.1f && m_fSoarInner >= -0.1f) //범위 0에 가까우면
	{
		return true;
	}

	DEBUG_LOG(L"Soar Inner", m_fSoarInner);
	Go_Straight();

	return false;
}

void Enemy::Create_RandPos()
{
	m_vRandPos.y = m_transform->position.y + rand() % 1001 - 500;
	m_vRandPos.x = m_transform->position.x + rand() % 1001 - 500;
	m_vRandPos.z = m_transform->position.z + rand() % 1001 - 500;

}

bool Enemy::Shoot()
{
	if (m_iCurRound > 0)
	{
		m_fFpmDelta += dTime;

		if (m_fFpmDelta >= 60.f / m_fFpm && Fov_Check())
		{
			Bullet_Manager::GetInstance()->Fire(m_transform->position, m_transform->rotation);

			--m_iCurRound;

			m_fFpmDelta = 0.f;
			return true;
		}
	}

	return false;
	//따발총
}


void Enemy::Reloading()
{
	if (m_iCurRound <= 0)
	{
		m_fRoundDelta += dTime;

		if (m_fRoundDelta >= 3.f)
		{
			m_iCurRound = m_iFullRound;

			m_fRoundDelta = 0.f;
		}
	}
	
}

bool Enemy::Missile()
{
	//미사일 
	if (m_iCurRound_Missile > 0)
	{
		m_fFpmDelta_Missile += dTime;

		if (m_fFpmDelta_Missile >= 60.f / m_fFpm_Missile)
		{
			Bullet_Manager::GetInstance()->Fire_Missile(m_transform->position, m_transform->rotation);

			--m_iCurRound_Missile;

			m_fFpmDelta_Missile = 0.f;
			return true;
		}
	}
	return false;
}

bool Enemy::Missile_Reloading()
{
	if (m_iCurRound_Missile <= 0)
	{
		m_fRoundDelta_Missile += dTime; 
		
		if (m_fRoundDelta_Missile >= 3.f)
		{
			m_iCurRound_Missile = m_iFullRound_Missile;

			m_fRoundDelta_Missile = 0.f;
			return false;
		}
		return true;
	}
	return false;
}

void Enemy::Decelerate()
{	
	if (m_fDist_Target <= 80.f && m_fSpd >= 10.f)
	{
		m_fSpd -= dTime * 3.f;
	}
}

void Enemy::Accelerate()
{
	if (m_fDist_Target >= 100 && m_fSpd <= m_fMaxSpd)
	{
		m_fSpd += dTime * 5.f;
	}
}

void Enemy::Kiting()
{
	//쏘면서 다가오다가 확 꺽기



}

void Enemy::Chase()
{
	//존나 달려와서 존나 쏴 그냥
	//Target_Setting(true);
	//Target_Update();

	if (!m_bChaseMove)
	{
		Look_Target();
		Go_Straight();

		if (m_fDist_Target <= 80.f && m_fDist_Target >= 20.f)
		{
			Shoot();
		}

		//가까워지면 거리 좀 벌릴때 까지 이동.
		if (m_fDist_Target <= 20.f)
		{
			m_bChaseMove = true;
		}
	}

	if (m_bChaseMove)
	{
		m_fChaseDelta += dTime;
		Go_Straight();

		if (m_fChaseDelta >= 3.f)
		{
			m_bChaseMove = false;
		}
	}
	

	


}

void Enemy::Drop()
{
	//플레이어를 따라오거나 맞은편에서 다가오다가
	//수평에 가까우면 폭탄 쏘고 ㅌㅌㅌ

	//Target_Setting(true);
	//Target_Update();
	
	int i = -1;

	if (!m_bDropMove)
	{
		Look_Target();
		Go_Straight();

		if (m_fDist_Target <= 150.f && m_fInner >= 0.9f)
		{
			if (Missile())
			{
				i = rand() % 2;
				m_bDropMove = true;
				m_vOriginForward = m_transform->GetForward();
			}
		}
	}
	
	
	
	if(i == 0)
	{
		m_bDive = true;
	}
	if (i == 1)
	{
		m_bSoar = true;
	}
	

	if (m_bDive)
	{
		if (Dive())
		{
			m_bRandMove = true;
			Create_RandPos();
			//m_bDive = false;
			//m_bDropMove = false;
			//여기서 일정시간동안 랜덤으루다가 움직이다가
			//다시 플레이어 고정.
		}
	}

	if (m_bSoar)
	{
		if (Soar())
		{
			m_bRandMove = true;
			Create_RandPos();
			//m_bSoar = false;
			//m_bDropMove = false;
		}
	}
	
	if (m_bRandMove)
	{
		
		Go_ToPos(m_vRandPos);
	
		m_fDropDelta += dTime;

		if (m_fDropDelta >= 5.f)
		{

			m_fDropDelta = 0.f;

			m_bRandMove = false;
			
			m_bDive = false;
			m_bSoar = false;
			
			m_bDropMove = false;
		
			Target_Setting(true);
		
		}
	

	}



#pragma region Failed
	//if (Missile_Reloading())
	//{
	//	Go_ToPos(m_vRandPos);
	//}
	//else 
	//{
	//	Target_Setting(true);
	//	Target_Update();
	//	Look_Target();

	//	Go_Straight();

	//	if (m_fDist_Target <= 100.f)
	//	{
	//		if (Missile())
	//		{
	//			m_vRandPos.y = m_transform->position.y + rand() % 501 - 250;
	//			m_vRandPos.x = m_transform->position.x + rand() % 501 - 250;
	//			m_vRandPos.z = m_transform->position.z + rand() % 501 - 250;
	//		}
	//	}
	//}
#pragma endregion

}

void Enemy::Hold()
{
	//그냥 자리에 홀드 박아놓고 두두두두두두두
	//쏘다가 일정거리 이상 들어오면 ㅌㅌㅌㅌ 하다가 다시 자리잡기

	//m_fHoldDelta += dTime; _pos

	if (m_fDist_Target >= 50.f && m_iCurRound != 0)
	{
		m_bHoldMove = false;
		//Target_Setting(true);
		//Target_Update();
		Look_Target();
		Shoot();
	}
	else 
	{ 
		Create_RandPos();

		m_bHoldMove = true; 
	}
	
	if(m_bHoldMove)
	{//그냥 일정 시간동안 움직이기
		//m_bHoldMove = true;

		if (m_fHoldDelta == 0.f)
		{ //이거보다 플레이어 기준에서 얼마정도 떨어진 곳?
			//원래 랜덤위치 있었음.
		}

		m_fHoldDelta += dTime;

		Go_ToPos(m_vRandPos);

		if (m_fHoldDelta >= 3.f)
		{
			m_bHoldMove = false;
			m_fHoldDelta = 0.f;
		}
	}

}

 