#include "stdafx.h"
#include "..\Include\Enemy.h"

#include "Bullet_Manager.h"


Enemy::Enemy(Desc * _Desc)
{
	m_fSpd = _Desc->fSpd;
	m_fLookSpd = _Desc->fLookSpd;
	m_fFpm = _Desc->fFpm;
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	Target_Setting(true);
}

void Enemy::Update()
{

	Target_Update();

	//Look_Target();
	//Horizontally();
	Rush();
	//Go_Straight();
	
	//if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_SPACE))
	//{
	//	Shoot();
	//}
	
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_RIGHT_ARROW))
	{
		Quaternion qTemp = m_transform->RotateAxis(m_transform->GetUp(), -dTime*10.f);
		m_transform->rotation *= qTemp;
	}
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_ARROW))
	{
		Quaternion qTemp = m_transform->RotateAxis(m_transform->GetUp(), dTime*10.f);
		m_transform->rotation *= qTemp;
	}
#pragma region DebugLog
	//DEBUG_LOG(L"Target On?", bTarget);
	DEBUG_LOG(L"타겟 까지의 거리", m_fDist_Target);
	DEBUG_LOG(L"타겟과의 내적 값", m_fInner);
	//DEBUG_LOG(L"UpVector과의 내적 값", m_fUpInner);
	//DEBUG_LOG(L"Up Angle", m_fUpAngle);
	DEBUG_LOG(L"Player is in the Enemy Fov", m_bFov);
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

		bTarget = false;
	}
	else 
	{
		m_pTarget = nullptr;
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
	else { m_bFov = false; 
	return false;
	}

	
}

void Enemy::Damaged(const int & _playerDmg)
{
}

const int & Enemy::Get_Damage()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return int(0);
}

const int & Enemy::Get_FullHp()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return int(0);
}

const int & Enemy::Get_CurHp()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return int(0);
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
	//	ㄴㄴㄴㄴ지금 0~ 0.5 0.5~1 처럼 주면 시작지점에서의 각도가 90도 이상이여야함.
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

void Enemy::Dive()
{

}

void Enemy::Soar()
{

}

void Enemy::Shoot()
{
	m_fFpmDelta += dTime;

	if (m_fFpmDelta >= 60.f/m_fFpm && Fov_Check())
	{
		Bullet_Manager::GetInstance()->Fire(m_transform->position, m_transform->rotation);
		m_fFpmDelta = 0.f;
	}

	//따발총
}

void Enemy::Misile()
{
	//미사일 
}

void Enemy::Rush()
{//멀리서 총쏘면서 다가오는거
	//0. 플레이어 시야각 안에서 생성
	//1. 타겟 세팅 (완전 플레이어 pos가 아니라 그 주위에서)
	//2. LookTarget하면서 오다가
	//3. Distance 어느 정도 오면 발사 하고 LookTarget풀기
	//4. 그 방향으로 이동하다가 Turn으로 방향바꾸고 다시 다른 패턴

	if (m_fDist_Target <= 50.f)
	{
		Shoot();

	}
	
	

}

void Enemy::Chase()
{//뒤에서 총 쏘면서 쫓아오는거
	//0. 타겟 세팅 완전 그 플레이어
	//1. 뒤에서 달려오면서 총 쏨
	//2. 만약 플레이어가 급 정거 등등 하면 관성처럼 약간은 앞으로 가서 회전하기.

}

void Enemy::Drop()
{//폭탄 떨구고 급선회 하는거
	//0. 아무래도 앞에서 달려오다가 미사일 발사하고 확 도는거

}

void Enemy::Hold()
{
	//그냥 자리에 홀드 박아놓고 두두두두두두두
}

 