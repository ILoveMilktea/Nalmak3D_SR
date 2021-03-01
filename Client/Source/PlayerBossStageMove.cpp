#include "stdafx.h"
#include "..\Include\PlayerBossStageMove.h"


PlayerBossStageMove::PlayerBossStageMove()
{
}


PlayerBossStageMove::~PlayerBossStageMove()
{
}

void PlayerBossStageMove::Initialize()
{
}

void PlayerBossStageMove::EnterState()
{
}

void PlayerBossStageMove::UpdateState()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_W))
	{
		m_transform->position.y += dTime * 20.f;
	}
	else if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_S))
	{
		m_transform->position.y -= dTime * 20.f;
	}

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_D))
	{
		m_transform->position.x += dTime *20.f;
	}
	else if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_A))
	{
		m_transform->position.x -= dTime *20.f;
	}
}

void PlayerBossStageMove::ExitState()
{
}
