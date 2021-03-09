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
}

void State_Evasion_Midboss::EnterState()
{
	EnemyManager::GetInstance()->MidBoss_Spawn(_MIDBOSS_SPAWNPOS);
}

void State_Evasion_Midboss::UpdateState()
{
}

void State_Evasion_Midboss::ExitState()
{
}
