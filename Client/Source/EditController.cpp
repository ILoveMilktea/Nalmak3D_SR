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
		CanvasGroup::GetInstance()->SetGroupFade(CANVAS_GROUP_NONE, 0.5f);
	}
	if (m_input->GetKeyDown(KEY_STATE_F2))
	{
		CanvasGroup::GetInstance()->SetGroupFade(CANVAS_GROUP_G1, 0.5f);
	}
	if (m_input->GetKeyDown(KEY_STATE_F3))
	{
		CanvasGroup::GetInstance()->SetGroupFade(CANVAS_GROUP_G2, 0.5f);
	}
	if (m_input->GetKeyDown(KEY_STATE_F4))
	{
		CanvasGroup::GetInstance()->SetGroupFade(CANVAS_GROUP_NONE, 1.f);
		CanvasGroup::GetInstance()->SetGroupFade(CANVAS_GROUP_G1, 1.f);
		CanvasGroup::GetInstance()->SetGroupFade(CANVAS_GROUP_G2, 1.f);
	}
}
