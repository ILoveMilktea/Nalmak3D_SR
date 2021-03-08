#include "stdafx.h"
#include "..\Include\State_Evasion_Midboss.h"

#include "Stage2_Mainstream_Define.h"

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
	EnemyManager::GetInstance()->MidBoss_Spawn(Vector3(0.f, 100.f, 50.f));
}

void State_Evasion_Midboss::UpdateState()
{
}

void State_Evasion_Midboss::ExitState()
{
}
