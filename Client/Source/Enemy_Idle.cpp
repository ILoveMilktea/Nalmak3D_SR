#include "stdafx.h"
#include "..\Include\Enemy_Idle.h"
#include "Enemy.h"


Enemy_Idle::Enemy_Idle()
{

}
Enemy_Idle::~Enemy_Idle()
{

}

void Enemy_Idle::Initialize()
{
}

void Enemy_Idle::EnterState()
{
	m_gameObject->GetComponent<Enemy>()->Target_Setting(true);
}

void Enemy_Idle::UpdateState()
{
	m_gameObject->GetComponent<Enemy>()->Target_Update();
	m_gameObject->GetComponent<Enemy>()->Look_Target();
}

void Enemy_Idle::ExitState()
{
}
