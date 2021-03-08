#include "stdafx.h"
#include "..\Include\Enemy_Debugging.h"
#include "Enemy.h"


Enemy_Debugging::Enemy_Debugging()
{
}


Enemy_Debugging::~Enemy_Debugging()
{
}

void Enemy_Debugging::Initialize()
{
}

void Enemy_Debugging::EnterState()
{
	m_pEnemy = m_gameObject->GetComponent<Enemy>();
	assert(L"Can't find Enemy compoent"&& m_pEnemy);

	m_pEnemy->Target_Setting(true);
	m_pEnemy->Target_Update();
	m_pEnemy->Look_Target();
}

void Enemy_Debugging::UpdateState()
{
	m_pEnemy->Target_Update();
	m_pEnemy->Look_Target();
	m_pEnemy->Fire_Gun();
}

void Enemy_Debugging::ExitState()
{
}
