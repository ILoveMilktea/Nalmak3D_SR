#include "stdafx.h"
#include "..\Include\State_Evasion_Midboss.h"

#include "Stage2_Mainstream_Define.h"
#include "MidBoss_Define.h"

#include "EnemyManager.h"

State_Evasion_Midboss::State_Evasion_Midboss()
{
}


State_Evasion_Midboss::~State_Evasion_Midboss()
{
}

void State_Evasion_Midboss::Initialize()
{
	m_mainCam = Core::GetInstance()->GetMainCamera()->GetTransform();
}

void State_Evasion_Midboss::EnterState()
{

	EnemyManager::GetInstance()->MidBoss_Spawn(_MIDBOSS_SPAWNPOS);
}

void State_Evasion_Midboss::UpdateState()
{
	DEBUG_LOG(L"cam", m_mainCam);
}

void State_Evasion_Midboss::ExitState()
{
}
