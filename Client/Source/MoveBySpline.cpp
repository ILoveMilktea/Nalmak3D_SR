#include "stdafx.h"
#include "..\Include\MoveBySpline.h"

MoveBySpline::MoveBySpline(Desc * _desc)
{
	m_isLoop = _desc->isLoop;
	m_isPlay = _desc->isPlay;
	m_moveTimePerSec = 1 / _desc->moveTime;
	m_timer = 0;
}

MoveBySpline::~MoveBySpline()
{
}

void MoveBySpline::Initialize()
{
}

void MoveBySpline::Update()
{
	if (m_isPlay)
	{
		m_timer += dTime * m_moveTimePerSec;
		DEBUG_LOG(L"timer", m_timer);
		if (m_timer > 1)
		{
			m_isPlay = m_isLoop;
			m_timer = 0;
		}
		m_transform->position = m_spline.GetPoint(m_timer);
	}

	

}

MoveBySpline* MoveBySpline::AddSplinePoint(const Vector3 & _point)
{
	m_spline.AddPoint(_point);
	return this;
}
