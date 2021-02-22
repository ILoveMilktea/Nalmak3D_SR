#include "stdafx.h"
#include "PlayerIdle.h"
#include "PlayerInfoManager.h"

PlayerIdle::PlayerIdle()
{
}


PlayerIdle::~PlayerIdle()
{
}

void PlayerIdle::Initialize()
{
	m_inputManager = InputManager::GetInstance();
	m_playerInfoManager = PlayerInfoManager::GetInstance();
	m_timeManager = TimeManager::GetInstance();
	m_stateControl = GetComponent<StateControl>();
}

void PlayerIdle::EnterState()
{
}

void PlayerIdle::UpdateState()
{
	if (m_inputManager->GetKeyPress(KEY_STATE_W))
	{
		SetInteger(L"MoveDir", 0);
		m_stateControl->SetState(L"playerMove");

	}
	/*else if (m_inputManager->GetKeyPress(KEY_STATE_A))
	{
		SetInteger(L"MoveDir", 1);
		m_stateControl->SetState(L"playerMove");
	}
	else if (m_inputManager->GetKeyPress(KEY_STATE_S))
	{
		SetInteger(L"MoveDir", 2);
		m_stateControl->SetState(L"playerMove");
	}
	else if (m_inputManager->GetKeyPress(KEY_STATE_W))
	{
		SetInteger(L"MoveDir", 3);
		m_stateControl->SetState(L"playerMove");
	}*/



}

void PlayerIdle::ExitState()
{
}
