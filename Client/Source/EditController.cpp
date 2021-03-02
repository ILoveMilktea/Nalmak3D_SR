#include "stdafx.h"
#include "..\Include\EditController.h"
#include "EnemyManager.h"

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
	}
	if (m_input->GetKeyDown(KEY_STATE_F2))
	{

	}
	if (m_input->GetKeyDown(KEY_STATE_F3))
	{
	}
	if (m_input->GetKeyDown(KEY_STATE_F4))
	{
		EnemyManager::GetInstance()->Destroy_AllEnemy();
	}
	if (m_input->GetKeyDown(KEY_STATE_F5))
	{
	}
	if (m_input->GetKeyDown(KEY_STATE_F6))
	{
	}
	if (m_input->GetKeyDown(KEY_STATE_F7))
	{

	}
	if (m_input->GetKeyDown(KEY_STATE_F8))
	{
		CanvasGroup::GetInstance()->AllOn();
	}
	if (m_input->GetKeyDown(KEY_STATE_F9))
	{
		CanvasGroup::GetInstance()->AllOff();
	}
}
