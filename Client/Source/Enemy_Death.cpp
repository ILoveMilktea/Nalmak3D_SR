#include "stdafx.h"
#include "..\Include\Enemy_Death.h"


Enemy_Death::Enemy_Death()
{
}


Enemy_Death::~Enemy_Death()
{
}

void Enemy_Death::Initialize()
{
	//this state only destory Instance.

}

void Enemy_Death::EnterState()
{
	//m_pEnemy = m_gameObject->GetComponent<Enemy>();

	//assert(L"�� ���� ���ʹ� �� ã���� ���ٰ� ����" && m_pEnemy);

	//m_pEnemy->Target_Setting(false);

	DESTROY(m_gameObject); //��!
}

void Enemy_Death::UpdateState()
{
	DEBUG_LOG(L"Enemy State", L"Death");
}

void Enemy_Death::ExitState()
{
}




