#include "stdafx.h"
#include "..\Include\Enemy_Chase.h"

#include "Enemy.h"
#include "Bullet_Manager.h"


Enemy_Chase::Enemy_Chase()
{
	
}


Enemy_Chase::~Enemy_Chase()
{
}

void Enemy_Chase::Initialize()
{	
	
}

void Enemy_Chase::EnterState()
{
	m_pEnemy = m_gameObject->GetComponent<Enemy>();

	assert(L"아 ㅋㅋ 에너미 못찾겠다고 ㅋㅋㄹㅇ" && m_pEnemy);

	m_pEnemy->Target_Setting(true);
}

void Enemy_Chase::UpdateState()
{
	if (!m_bAvoid)
	{
		m_pEnemy->Target_Update();
		m_pEnemy->Look_Target();
		m_pEnemy->Accelerate();
		m_pEnemy->Go_Straight();

		//float m_dist = m_pEnemy->Get_Distance();

		if (m_pEnemy->Get_Distance() <= 80.f && m_pEnemy->Get_Distance() >= 20.f)
		{
			m_pEnemy->Decelerate();
			m_pEnemy->Fire_Gun();
		}

		if (m_pEnemy->Get_Distance() <= 20.f)
		{
			m_bAvoid = true;
		}
	}

	if (m_bAvoid)
	{
		//if u wanna dramatic effect,
		//Enemy located upper than player, soar.
		//or Enemy located downner than player, dive.

		m_pEnemy->Go_Straight();
		
		m_fAvoidDelta += dTime;

		if (m_fAvoidDelta >= 3.f)
		{
			m_fAvoidDelta = 0.f;
			m_bAvoid = false;
		}
	}

	
}

void Enemy_Chase::ExitState()
{

}

