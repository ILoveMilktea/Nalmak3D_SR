#include "stdafx.h"
#include "..\Include\Enemy_Chase.h"

#include "Enemy.h"

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
	//int i = m_pEnemy->Get_CurHp();
}

void Enemy_Chase::UpdateState()
{
}

void Enemy_Chase::ExitState()
{
}
