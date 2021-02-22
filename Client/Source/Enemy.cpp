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
	DEBUG_LOG(L"Ÿ�� ������ �Ÿ�", m_fDist_Target);
	DEBUG_LOG(L"Ÿ�ٰ��� ���� ��", m_fInner);
	//DEBUG_LOG(L"UpVector���� ���� ��", m_fUpInner);
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
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return int(0);
}

const int & Enemy::Get_FullHp()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return int(0);
}

const int & Enemy::Get_CurHp()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return int(0);
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
	//	������������ 0~ 0.5 0.5~1 ó�� �ָ� �������������� ������ 90�� �̻��̿�����.
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

	//������
}

void Enemy::Misile()
{
	//�̻��� 
}

void Enemy::Rush()
{//�ָ��� �ѽ�鼭 �ٰ����°�
	//0. �÷��̾� �þ߰� �ȿ��� ����
	//1. Ÿ�� ���� (���� �÷��̾� pos�� �ƴ϶� �� ��������)
	//2. LookTarget�ϸ鼭 ���ٰ�
	//3. Distance ��� ���� ���� �߻� �ϰ� LookTargetǮ��
	//4. �� �������� �̵��ϴٰ� Turn���� ����ٲٰ� �ٽ� �ٸ� ����

	if (m_fDist_Target <= 50.f)
	{
		Shoot();

	}
	
	

}

void Enemy::Chase()
{//�ڿ��� �� ��鼭 �Ѿƿ��°�
	//0. Ÿ�� ���� ���� �� �÷��̾�
	//1. �ڿ��� �޷����鼭 �� ��
	//2. ���� �÷��̾ �� ���� ��� �ϸ� ����ó�� �ణ�� ������ ���� ȸ���ϱ�.

}

void Enemy::Drop()
{//��ź ������ �޼�ȸ �ϴ°�
	//0. �ƹ����� �տ��� �޷����ٰ� �̻��� �߻��ϰ� Ȯ ���°�

}

void Enemy::Hold()
{
	//�׳� �ڸ��� Ȧ�� �ھƳ��� �εεεεεε�
}

 