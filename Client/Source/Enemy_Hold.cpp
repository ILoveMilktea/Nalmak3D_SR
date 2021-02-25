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
	{//�׳� ���� �ð����� �����̱�
	 //m_bHoldMove = true;

		if (m_fAvoidDelta == 0.f)
		{ //�̰ź��� �÷��̾� ���ؿ��� ������ ������ ��?
		  //���� ������ġ �־���.
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
               