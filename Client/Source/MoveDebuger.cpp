#include "stdafx.h"
#include "..\Include\MoveDebuger.h"
#include "InputManager.h"


MoveDebuger::MoveDebuger(Desc * _desc)
{
}

MoveDebuger::~MoveDebuger()
{
}

void MoveDebuger::Initialize()
{
}

void MoveDebuger::Update()
{
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_UP_ARROW))
	{
		m_transform->position.z += 5.f * dTime;
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_ARROW))
	{
		m_transform->position.x -= 5.f * dTime;
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_DOWN_ARROW))
	{
		m_transform->position.z -= 5.f * dTime;
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_ARROW))
	{
		m_transform->position.x += 5.f * dTime;
	}
}
