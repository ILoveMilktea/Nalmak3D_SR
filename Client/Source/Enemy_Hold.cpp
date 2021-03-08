#include "stdafx.h"
#include "..\Include\Enemy_Hold.h"
#include "Enemy.h"


Enemy_Hold::Enemy_Hold()
{
}


Enemy_Hold::~Enemy_Hold()
{
}

void Enemy_Hold::Initialize()
{
}

void Enemy_Hold::EnterState()
{
	m_pEnemy = m_gameObject->GetComponent<Enemy>();
	assert(L"�� ���� ���ʹ� ��ã�ڴٰ� ��������" && m_pEnemy);

	m_pEnemy->Target_Setting(true);
	m_pEnemy->Target_Update();
	m_pEnemy->Look_Target();

	m_pEnemy->Set_LookSpd(3.f);
}

void Enemy_Hold::UpdateState()
{

	m_pEnemy->Target_Update();


	if (!m_bAvoid)
	{
		//m_pEnemy->Target_Update();
		m_pEnemy->Look_Target();
		m_pEnemy->Fire_Gun();
		m_bAvoid = false;

		if(m_pEnemy->Get_Distance() < 50.f || m_pEnemy->Get_GunCurRound() <= 0)
		{
			m_pEnemy->Create_RandPos();
			m_pEnemy->Set_Accel(true);
			m_bAvoid = true;
		}
	}

	if (m_bAvoid)
	{//�׳� ���� �ð����� �����̱�

		m_fAvoidDelta += dTime;
		
		m_pEnemy->Go_ToPos(m_pEnemy->Get_RandPos());
		m_pEnemy->Go_Straight();


		if (m_fAvoidDelta >= 5.f)
		{
			m_pEnemy->Set_Accel(false);
		}

		if (m_pEnemy->Get_CurSpd() <= 3.f)
		{
			m_fAvoidDelta = 0.f;
			m_bAvoid = false;
		}

		//if (m_fAvoidDelta >= 4.f)
		//{
		//	m_fAvoidDelta = 0.f;
		//	m_bAvoid = false;
		//}
	}
}

void Enemy_Hold::ExitState()
{
}
               