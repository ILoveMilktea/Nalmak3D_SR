#include "stdafx.h"
#include "..\Include\Enemy_Drop.h"

#include "Enemy.h"


Enemy_Drop::Enemy_Drop()
{
}


Enemy_Drop::~Enemy_Drop()
{
}

void Enemy_Drop::Initialize()
{
}

void Enemy_Drop::EnterState()
{
	m_pEnemy = m_gameObject->GetComponent<Enemy>();
	assert(L"Enemy Component can't find" && m_pEnemy);
}

void Enemy_Drop::UpdateState()
{
	
	int iRandPattern = -1;

	if (!m_bAvoid)
	{
		m_pEnemy->Target_Update();
		m_pEnemy->Look_Target();
		m_pEnemy->Go_Straight();

		//if (m_pEnemy->Get_Distance() <= 70.f /*&& m_pEnemy->Get_Distance() > 50.f*/
		//	&& m_pEnemy->Get_Inner() >= 0.8f)
		//{
		//	m_pEnemy->Set_Accel(false);
		//}


		if (m_pEnemy->Get_Distance() <= 50.f && m_pEnemy->Get_Inner() >= 0.9f)
		{
			if (m_pEnemy->Fire_Missile())
			{
				iRandPattern = rand() % 2;
				m_pEnemy->Set_OriginForward();
				m_bAvoid = true;
			}
		}
	}

	if (m_bAvoid)
	{
		if (iRandPattern == DoDive)
		{
			m_bDive = true;
			iRandPattern = -1;
			//m_pEnemy->Set_Accel(true);
		}
		if (iRandPattern == DoSoar)
		{
			m_bSoar = true;
			iRandPattern = -1;
			//m_pEnemy->Set_Accel(true);
		}


		if (m_bDive)
		{
			if (m_pEnemy->Dive())
			{
				m_bRandMove = true;
				m_pEnemy->Create_RandPos();
				//여기서 일정시간동안 랜덤으루다가 움직이다가
				//다시 플레이어 고정.
			}
		}

		if (m_bSoar)
		{
			if (m_pEnemy->Soar())
			{
				m_bRandMove = true;
				m_pEnemy->Create_RandPos();
			}
		}

		if (m_bRandMove)
		{

			m_pEnemy->Go_ToPos(m_pEnemy->Get_RandPos());

			m_fAvoidDelta += dTime;

			if (m_fAvoidDelta >= 3.f)
			{
				m_fAvoidDelta = 0.f;

				m_bRandMove = false;

				m_bDive = false;
				m_bSoar = false;

				m_bAvoid = false;

				m_pEnemy->Target_Setting(true);
			}
		}
	}
}

void Enemy_Drop::ExitState()
{

}
