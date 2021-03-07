#include "stdafx.h"
#include "..\Include\Player_Boss_Move.h"


Player_Boss_Move::Player_Boss_Move()
{
}


Player_Boss_Move::~Player_Boss_Move()
{
}

void Player_Boss_Move::Initialize()
{
}

void Player_Boss_Move::EnterState()
{
	
}

void Player_Boss_Move::UpdateState()
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
}

void Player_Boss_Move::ExitState()
{
}
