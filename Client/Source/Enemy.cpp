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
	DEBUG_LOG(L"Ÿ�� ������ �Ÿ�", m_fDist_Target);
	DEBUG_LOG(L"Ÿ�ٰ��� ���� ��", m_fInner);
	//DEBUG_LOG(L"UpVector���� ���� ��", m_fUpInner);
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
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_iAtt;
}

const int & Enemy::Get_FullHp()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_iFullHp;
}

const int & Enemy::Get_CurHp()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_iCurHp;
}

void Enemy::Set_Damage(const int & _dmg)
{
}

//�� �������� �� ���� 0�̸� ���� ���ߴ� �͸� �غ���.
void Enemy::Lean()
{
#pragma region Failed
	//if (!bTarget)
	//{
	//	return;
	//}
	///* angle? ���� ��ġ���� Ÿ�� ��ġ�� ���� ����?*/
	///* or ���� ������ ���� ������ ����?*/
	///* Ÿ�ٰ��� �Ÿ� ���Ϳ� ���� �������� �������� ���� ���ϰ�*/

	//m_fTurnDeltaTime += dTime;

	//if (m_fTurnDeltaTime >= m_fTurnUpdateTime)
	//{
	//	Vector3 vDir = m_Target->GetTransform()->position - m_transform->position;
	//	D3DXVec3Normalize(&vDir, &vDir);

	//	/* fInner -> ������ �����, cos��Ÿ ��. */
	//	/*float */m_fInner = D3DXVec3Dot(&vDir, &m_transform->GetForward());
	//	/*DEBUG_LOG(L"Inner ��", fInner);*/
	//	/* ���� ������ ���ϱ� ���ؼ��� ���ڻ��� ���� */
	//	/* ���� ������ ����. */
	//	float fRad = acosf(m_fInner);
	//	float fDegree = D3DXToDegree(fRad);

	//	/* ���� Ư¡ -> ����� ���� -1 ~ 0 ~ 1 */
	//		/* �������� -1�� ������ : �ٶ󺸰� �ִ� �ݴ��� ����� ���� ������. */
	//		/* �������� 0�� ������  : Ÿ�ٰ� ������ ������. */
	//		/* �������� 1�� ������  : �ٶ󺸰� �ִ� ����� ���� ������. */
	//		/* ��ü �ִ� ������ ���� : -50 ~ 0 ~ 50 */

	//	/* Ÿ���� �����ʿ� ���� ��쿡�� */
	//	//������ 0 ~ 0.5 ������ ���� ���� -> 
	//	//������ 0.5 ~ 1 ������ ���� ���� -> 1�� ��������� ������ �ǰ�.

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
	//	������������ 0 ~ 0.5 0.5 ~ 1 ó�� �ָ� �������������� ������ 90�� �̻��̿�����.
	//	�׷��� ����
	//	ó�� �� Ÿ�� ����� ��(SetTarget) ���� Inner ����
	//	Ÿ�ٿ� ���������� Inner���� ��з��� ������ ������ �ɾ����
	//	���� �ʰڳ� �̰ž�.
	//		=> ���߿� �÷��̾ Ÿ������ ���������� �÷��̾� �̵����� �������� �ҵ�?
	//	*/
	//	if (m_fInner >= m_fInner_First && m_fInner <= (m_fInner_First+ m_fInner_Goal)/2.f)
	//	{ //���� ���� ��
	//		m_fTurnRotZ = (-50 * m_fInner + 50) * dTime * m_fTurnSpd;

	//		Quaternion qTemp = m_transform->RotateAxis(m_transform->GetForward(), -m_fTurnRotZ);
	//		m_transform->rotation *= qTemp;
	//	}
	//	if (m_fInner >(m_fInner_First + m_fInner_Goal) / 2.f && m_fInner <= 0.9f)
	//	{ //�������� ���� ���� ��
	//		m_fTurnRotZ = (-50 * m_fInner + 50) * dTime * m_fTurnSpd;

	//		Quaternion qTemp = m_transform->RotateAxis(m_transform->GetForward(), m_fTurnRotZ);
	//		m_transform->rotation *= qTemp;
	//	}

	//	//���� �ݴ��� �־ ������ ������ ȥ�� ȸ���ϰ� ��123����
	//	//���� ���� ������ 
	//	
	//	

	//	/* Ÿ�ٰ��� ������ �������� 1�� �������, 90���� ��������� 0*/
	//	/* ������ �������� 0, �־����� 50 */
	//	/* 1�϶� 0, 0�϶� 50.f*/

	//	//fRotZ = 0.f;
	//	//fRotZ = -50 * fInner + 50;
	//	//DEBUG_LOG(L"fRotZ ��", fRotZ);

	//	//m_QuartRot *= temp;

	//	/*Ȯ�ο�*/
	//	//float fTemp;
	//	//fTemp = 0.f;

	//	//if(fInner >= 0.95)
	//	//fTemp = (-50 * fInner + 50) * -dTime;
	//	
	//	//DEBUG_LOG(L"Temp fRotZ ��", fTemp);
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

	// ���̺�,�Ҿ� �� �� ���� �Ҷ� ���� forward�� �޾� ���ٰ� 
	// �� ���̶� ���ؼ� ������ �ɶ����� ��ü ����
	Vector3 Z = m_transform->GetForward();
	//Vector3 WorldY = { 0.f,1.f,0.f };

	m_fDiveInner = D3DXVec3Dot(&Z, &m_vOriginForward);

	if (m_fDiveInner <= 0.1f && m_fDiveInner >= -0.1f) //���� 0�� ������
	{
		return true;
	}

	DEBUG_LOG(L"���̺� Inner", m_fDiveInner);
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

	if (m_fSoarInner <= 0.1f && m_fSoarInner >= -0.1f) //���� 0�� ������
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
	//������
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
	//�̻��� 
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
	//��鼭 �ٰ����ٰ� Ȯ ����



}

void Enemy::Chase()
{
	//���� �޷��ͼ� ���� �� �׳�
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

		//��������� �Ÿ� �� ������ ���� �̵�.
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
	//�÷��̾ ������ų� �������� �ٰ����ٰ�
	//���� ������ ��ź ��� ������

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
			//���⼭ �����ð����� ��������ٰ� �����̴ٰ�
			//�ٽ� �÷��̾� ����.
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
	//�׳� �ڸ��� Ȧ�� �ھƳ��� �εεεεεε�
	//��ٰ� �����Ÿ� �̻� ������ �������� �ϴٰ� �ٽ� �ڸ����

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
	{//�׳� ���� �ð����� �����̱�
		//m_bHoldMove = true;

		if (m_fHoldDelta == 0.f)
		{ //�̰ź��� �÷��̾� ���ؿ��� ������ ������ ��?
			//���� ������ġ �־���.
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

 