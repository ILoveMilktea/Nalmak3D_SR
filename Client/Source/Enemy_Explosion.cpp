#include "stdafx.h"
#include "..\Include\Enemy_Explosion.h"
#include "Enemy.h"


Enemy_Explosion::Enemy_Explosion()
{
}


Enemy_Explosion::~Enemy_Explosion()
{
}

void Enemy_Explosion::Initialize()
{
}

void Enemy_Explosion::EnterState()
{
	m_pEnemy = m_gameObject->GetComponent<Enemy>();

	assert(L"�� ���� ���ʹ� �� ã���� ���ٰ� ����" && m_pEnemy);

	//boom effect create
}

void Enemy_Explosion::UpdateState()
{
	//boom 

	//if boom effect finised
	//change state to Destory

	DEBUG_LOG(L"Enemy State", L"explosion");
	
	SetState(L"Death");
	return;

}

void Enemy_Explosion::ExitState()
{

}
