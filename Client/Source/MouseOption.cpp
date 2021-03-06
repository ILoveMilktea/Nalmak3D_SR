#include "stdafx.h"
#include "..\Include\MouseOption.h"


MouseOption::MouseOption(Desc * _desc)
{
	m_mouseShadow = _desc->shadowCheck;
}

MouseOption::~MouseOption()
{
}
// Press the space bar to see the mouse.
//	Airplane does not accept mouse input.
void MouseOption::Initialize()
{
	ShowCursor(m_mouseShadow);
	m_core = Core::GetInstance();
	m_inputManager = InputManager::GetInstance();
}

void MouseOption::Update()
{
	/*m_preMousePoint = m_curMousePoint;
	POINT point = {};
	GetCursorPos(&point);
	m_curMousePoint.x += (float)(point.x - m_core->GetWindowWidth() * 0.5f);
	m_curMousePoint.y += (float)(m_core->GetWindowHeight() * 0.5f - point.y);*/

	/*if (!m_mouseShadow)
	{
		m_preMousePoint = m_curMousePoint;
		POINT point = {};
		GetCursorPos(&point);
		m_curMousePoint.x += (float)(point.x - m_core->GetWindowWidth() * 0.5f);
		m_curMousePoint.y += (float)(m_core->GetWindowHeight() * 0.5f - point.y);
	}*/
	
}

void MouseOption::LateUpdate()
{
	if(!m_mouseShadow)
		SetCursorPos(HALF_WINCX, HALF_WINCY);

	if (m_inputManager->GetKeyDown(KEY_STATE_SPACE))
	{
		m_mouseShadow = !m_mouseShadow;
		ShowCursor(m_mouseShadow);
	}
	
}
