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

	if (m_input->GetKeyDown(KEY_STATE_F9))
	{
		CanvasGroup::GetInstance()->AllOff();
	}
	if (m_input->GetKeyDown(KEY_STATE_F8))
	{
		CanvasGroup::GetInstance()->AllOn();
	}
	if (m_input->GetKeyDown(KEY_STATE_F7))
	{

	}
	if (m_input->GetKeyDown(KEY_STATE_F6))
	{
	}
}
