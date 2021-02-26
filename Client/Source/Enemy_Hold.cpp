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
	assert(L"아 ㅋㅋ 에너미 못찾겠다고 ㅋㅋㄹㅇ" && m_pEnemy);

	m_pEnemy->Target_Setting(true);
	m_pEnemy->Target_Update();
	m_pEnemy->Look_Target();

}

void Enemy_Hold::UpdateState()
{
	if (!m_bAvoid)
	{
		if (m_pEnemy->Get_Distance() >= 50.f || m_pEnemy->Get_GunCurRound() != 0)
		{
			m_pEnemy->Target_Update();
			m_pEnemy->Look_Target();
			m_pEnemy->Shoot();
			m_bAvoid = false;
		}
		else
		{
			m_pEnemy->Create_RandPos();
			m_bAvoid = true;
		}
	}

	if (m_bAvoid)
	{//그냥 일정 시간동안 움직이기
	 //m_bHoldMove = true;

		if (m_fAvoidDelta == 0.f)
		{ //이거보다 플레이어 기준에서 얼마정도 떨어진 곳?
		  //원래 랜덤위치 있었음.
		}

		m_fAvoidDelta += dTime;

		m_pEnemy->Go_ToPos(m_pEnemy->Get_RandPos());

		if (m_fAvoidDelta >= 3.f)
		{
			m_fAvoidDelta = 0.f;
			m_bAvoid = false;
		}
	}
}

void Enemy_Hold::ExitState()
{
}
               