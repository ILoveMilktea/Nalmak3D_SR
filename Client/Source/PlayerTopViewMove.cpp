#include "stdafx.h"
#include "..\Include\PlayerTopViewMove.h"

#include "PlayerInfoManager.h"


PlayerTopViewMove::PlayerTopViewMove()
{
}


PlayerTopViewMove::~PlayerTopViewMove()
{
}

void PlayerTopViewMove::Initialize()
{
}

void PlayerTopViewMove::EnterState()
{
	
}

void PlayerTopViewMove::UpdateState()
{
	TopViewMoving();
}

void PlayerTopViewMove::ExitState()
{
}

void PlayerTopViewMove::TopViewMoving()
{
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W))
	{
		m_transform->position.z += 10.f * dTime;

	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S))
	{
		m_transform->position.z -= 10.f* dTime;
	}

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A))
	{
		m_transform->position.x -= 10.f* dTime;
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
	{
		m_transform->position.x += 10.f* dTime;
	}

	//횡 이동 할 때 z축 기울기 추가해주기

	
}

void PlayerTopViewMove::Shooting()
{
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_MOUSE))
	{

	}

	if(InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_MOUSE))
	{
	
	}
}
