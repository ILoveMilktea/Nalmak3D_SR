#include "stdafx.h"
#include "..\Include\Crosshair.h"

#define WINCENTER Vector2(WINCX*0.5f, WINCY*0.5f)

Crosshair::Crosshair(Desc * _desc)
	:SingleImage(&_desc->img_desc)
{
	m_width = _desc->width;
	m_height = _desc->height;

	m_limitBoundary.left	= LONG(-_desc->width * 0.5f);
	m_limitBoundary.right	= LONG(_desc->width * 0.5f);
	m_limitBoundary.top		= LONG(-_desc->height * 0.5f);
	m_limitBoundary.bottom	= LONG(_desc->height * 0.5f);

	m_mousePosition = WINCENTER;
}

void Crosshair::UpdatePosition(SetVector2Func _setValueFunc, GetVector2Func _getValueFunc)
{
	Vector2 mousePosition;
	_setValueFunc(&mousePosition, _getValueFunc);
	
	if (m_mousePosition != mousePosition)
	{

		Vector2 dir = mousePosition - WINCENTER;
		dir.x *= m_width / WINCX;
		if (dir.x < m_limitBoundary.left)
			dir.x = (float)m_limitBoundary.left;
		if (dir.x > m_limitBoundary.right)
			dir.x = (float)m_limitBoundary.right;

		dir.y *= m_height / WINCY;
		if (dir.x < m_limitBoundary.top)
			dir.x = (float)m_limitBoundary.top;
		if (dir.x > m_limitBoundary.bottom)
			dir.x = (float)m_limitBoundary.bottom;

		m_transform->position = { WINCENTER.x + dir.x, WINCENTER.y + dir.y, 0.f };
	}
}
