#include "stdafx.h"
#include "..\Include\State_Evasion_Airfire.h"

#include "Stage2_Mainstream_Define.h"
#include "MidBoss_Define.h"
#include "EnemyManager.h"
#include "InputManager.h"

State_Evasion_Airfire::State_Evasion_Airfire()
{
}


State_Evasion_Airfire::~State_Evasion_Airfire()
{
}

void State_Evasion_Airfire::Initialize()
{
	m_mainCam = Core::GetInstance()->GetMainCamera()->GetTransform();
}

void State_Evasion_Airfire::EnterState()
{	
	m_spawnTimer = 0.f;

	m_spawnPos[0] = Vector3(-70.f, -50.f, 150.f);
	m_spawnPos[1] = Vector3(70.f, -50.f, 100.f);
	m_spawnPos[2] = Vector3(-30.f, -50.f, 120.f);
	m_spawnPos[3] = Vector3(30.f, -50.f, 180.f);
	m_spawnPos[4] = Vector3(-70.f, -30.f, 150.f);
	m_spawnPos[5] = Vector3(70.f, -30.f, 160.f);
	m_spawnPos[6] = Vector3(-30.f, -30.f, 160.f);
	m_spawnPos[7] = Vector3(30.f, -30.f, 150.f);
}

void State_Evasion_Airfire::UpdateState()
{
	DEBUG_LOG(L"cam", m_mainCam);

	m_spawnTimer += dTime;

	if (m_spawnIndex < 4)
		Wave_1();
	else
		Wave_2();

	if (InputManager::GetInstance()->GetKeyDown(_NEXT_STATE_KEY))
	{
		SetState(_sn_midboss);
		return;
	}
}

void State_Evasion_Airfire::ExitState()
{
}

void State_Evasion_Airfire::Wave_1()
{
	if (m_spawnTimer > 2.f)
	{
		EnemyManager::GetInstance()->Enemy_Spawn_Evasion(AIRFIRE, _DOWNSPAWN, m_spawnPos[m_spawnIndex]);
		m_spawnTimer = 0.f;
		++m_spawnIndex;
	}
}

void State_Evasion_Airfire::Wave_2()
{
	if (m_spawnTimer > 0.5f)
	{
		if (m_spawnIndex == 8)
		{
			SetState(_sn_midboss);
			return;
		}

		EnemyManager::GetInstance()->Enemy_Spawn_Evasion(AIRFIRE, _DOWNSPAWN, m_spawnPos[m_spawnIndex - 4]);
		EnemyManager::GetInstance()->Enemy_Spawn_Evasion(AIRFIRE, _DOWNSPAWN, m_spawnPos[m_spawnIndex]);
		m_spawnTimer = 0.f;
		++m_spawnIndex;
	}
}
