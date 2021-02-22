#include "stdafx.h"
#include "..\Include\MouseOption.h"




MouseOption::MouseOption(Desc * _desc)
{
	m_mouseShadow = _desc->shadowCheck;
	m_fixMousePos = _desc->fixMousePos;
}

MouseOption::~MouseOption()
{
}

void MouseOption::Initialize()
{

	ShowCursor(m_mouseShadow);

}

void MouseOption::Update()
{
	
}

void MouseOption::LateUpdate()
{
	SetCursorPos(HALF_WINCX, HALF_WINCY);
}
