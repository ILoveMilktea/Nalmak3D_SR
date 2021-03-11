#include "stdafx.h"
#include "..\Include\DogFight_Stage2_Exit.h"


DogFight_Stage2_Exit::DogFight_Stage2_Exit()
{
}


DogFight_Stage2_Exit::~DogFight_Stage2_Exit()
{
}

void DogFight_Stage2_Exit::Initialize()
{
}

void DogFight_Stage2_Exit::EnterState()
{
	m_timer = 0.f;
}

void DogFight_Stage2_Exit::UpdateState()
{
	m_timer += dTime;
	
	if (m_timer > 1.f)
	{
		SetState(L"State_Evasion_Enter");
	}
		
}

void DogFight_Stage2_Exit::ExitState()
{
}
