#include "stdafx.h"
#include "..\Include\State_Player_Evasion.h"


State_Player_Evasion::State_Player_Evasion()
{
}


State_Player_Evasion::~State_Player_Evasion()
{
}

void State_Player_Evasion::Initialize()
{
}

void State_Player_Evasion::EnterState()
{
}

void State_Player_Evasion::UpdateState()
{
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W)
		&& m_transform->position.z < 45.f)
	{
		m_transform->position.z += 20.f * dTime;

	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S)
		&& m_transform->position.z > -45.f)
	{
		m_transform->position.z -= 20.f* dTime;
	}

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D)
		&& m_transform->position.x < 85.f)
	{
		m_transform->position.x += 20.f* dTime;
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A)
		&& m_transform->position.x > -85.f)
	{
		m_transform->position.x -= 20.f* dTime;
	}
}

void State_Player_Evasion::ExitState()
{
}
