#include "stdafx.h"
#include "..\Include\Enemy_Death.h"

#include "EnemyManager.h"

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
	EnemyManager::GetInstance()->Add_EnemyCount(-1);
	DESTROY(m_gameObject);
	m_gameObject = nullptr;
}

void Enemy_Death::UpdateState()
{
	
}

void Enemy_Death::ExitState()
{

}




