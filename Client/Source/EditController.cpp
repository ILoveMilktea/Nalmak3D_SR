#include "stdafx.h"
#include "..\Include\EditController.h"


EditController::EditController(Desc * _desc)
{
}

void EditController::Initialize()
{
	m_input = InputManager::GetInstance();
	m_editMode = false;
}

void EditController::Update()
{
	if (m_input->GetKeyDown(KEY_STATE_ESC))
	{
		PostQuitMessage(0);
	}

	if (m_input->GetKeyDown(KEY_STATE_TAB))
		m_editMode = true;
	
	if (!m_editMode)
		return;

	if (m_input->GetKeyDown(KEY_STATE_F1))
	{
		PlayerInfoManager::GetInstance()->SetMaxSpeed(10.f);
	}
	if (m_input->GetKeyDown(KEY_STATE_F2))
	{
		PlayerInfoManager::GetInstance()->SetMaxSpeed(20.f);
	}
	if (m_input->GetKeyDown(KEY_STATE_F3))
	{
		PlayerInfoManager::GetInstance()->SetMaxSpeed(30.f);
	}
	if (m_input->GetKeyDown(KEY_STATE_F4))
	{
	}
}
