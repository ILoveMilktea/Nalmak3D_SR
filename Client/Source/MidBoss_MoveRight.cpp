#include "stdafx.h"
#include "..\Include\MidBoss_MoveRight.h"

#include "EnemyManager.h"

#include "MidBoss_Headers.h"
#include "MidBoss_Define.h"


MidBoss_MoveRight::MidBoss_MoveRight()
{
}


MidBoss_MoveRight::~MidBoss_MoveRight()
{
}

void MidBoss_MoveRight::Initialize()
{
}

void MidBoss_MoveRight::EnterState()
{
	m_moveTimer = 0.f;
	m_spawnTimer = 0.f;
	m_stateTimer = 0.f;

	m_spawnTerm = 2.f;
	m_stateDuration = 5.f;

	int signX = (rand() % 2) == 0 ? -1 : 1;
	float randX = signX * (rand() % _MIDBOSS_RANDAMOUNT) * 0.1f;
	int signZ = (rand() % 2) == 0 ? -1 : 1;
	float randZ = signZ * (rand() % _MIDBOSS_RANDAMOUNT) * 0.1f;

	m_startPos = m_transform->position;
	m_destPos = _MIDBOSS_RIGHTPOS + Vector3(randX, 0.f, randZ);
}

void MidBoss_MoveRight::UpdateState()
{
	Move();
	Spawn();

	m_stateTimer += dTime;
	if (m_stateTimer >= m_stateDuration)
	{
		SetState(_sn_idle);
		return;
	}


#ifdef _DEBUG
	if (InputManager::GetInstance()->GetKeyDown(_NEXT_STATE_KEY))
	{
		SetState(_sn_idle);
		return;
	}
#endif // _DEBUG
}

void MidBoss_MoveRight::ExitState()
{
}

void MidBoss_MoveRight::Move()
{
	if (m_moveTimer > 1.f)
		return;

	float inverseRate = 1.f - m_moveTimer;
	float sLerpTimer = 1.f - inverseRate * inverseRate;
	m_transform->position = Nalmak_Math::Lerp(m_startPos, m_destPos, sLerpTimer);

	m_moveTimer += dTime;
}

void MidBoss_MoveRight::Spawn()
{
	m_spawnTimer += dTime;

	if (m_spawnTimer < m_spawnTerm)
		return;

	if (m_wave1)
	{
		EnemyManager::GetInstance()->Enemy_Spawn_Evasion(LOOK, _LEFTSPAWN, _LEFTDEST * 0.4f + _UPDEST * 1.2f, 6.f);
		EnemyManager::GetInstance()->Enemy_Spawn_Evasion(LOOK, _LEFTSPAWN, _LEFTDEST * 0.8f + _UPDEST * 0.8f, 6.f);
		EnemyManager::GetInstance()->Enemy_Spawn_Evasion(LOOK, _LEFTSPAWN, _LEFTDEST * 1.2f + _UPDEST * 0.5f, 6.f);
	}
	else
	{
		EnemyManager::GetInstance()->Enemy_Spawn_Evasion(CIRCLE, _UPSPAWN, _UPDEST * 0.5f, 4.f);
		EnemyManager::GetInstance()->Enemy_Spawn_Evasion(CIRCLE, _UPSPAWN, _LEFTDEST * 0.5f, 4.f);
	}

	m_wave1 = !m_wave1;

	m_spawnTimer = 0.f;
}
