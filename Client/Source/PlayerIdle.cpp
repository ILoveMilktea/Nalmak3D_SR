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
	m_stateControl->SetState(L"playerMove");
}

void PlayerIdle::UpdateState()
{
	/*if (m_inputManager->GetKeyPress(KEY_STATE_W))
	{
		SetInteger(L"MoveDir", 0);
		m_stateControl->SetState(L"playerMove");

	}*/



}

void PlayerIdle::ExitState()
{
}
