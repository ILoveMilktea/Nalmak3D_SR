#include "stdafx.h"
#include "..\Include\PlayerBossStageMove.h"
#include "Bullet_Manager.h"


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
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
	{
		m_transform->position.y += dTime * 20.f;
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		m_transform->position.y -= dTime * 20.f;
	}

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		m_transform->position.x += dTime *20.f;
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		m_transform->position.x -= dTime *20.f;
	}

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		Bullet_Manager::GetInstance()->Fire_Player(m_transform->position, m_transform->rotation, 150.f);
	}

}

void PlayerBossStageMove::ExitState()
{
}
