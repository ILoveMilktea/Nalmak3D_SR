#include "stdafx.h"
#include "..\Include\SingleLine.h"


SingleLine::SingleLine(Desc * _desc)
{
	m_point1 = _desc->point1;
	m_point2 = _desc->point2;
}

void SingleLine::Initialize()
{
	m_core = Core::GetInstance();
}

void SingleLine::Update()
{
	m_core->DrawLine(m_point1, m_point2);
}
