#include "stdafx.h"
#include "MoveBySpline.h"

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
	m_timer = 0;
}

void MoveBySpline::Update()
{
	DEBUG_LOG(L"dTime", dTime);

	if (m_isPlay)
	{
		m_transform->position = m_spline.GetPoint(m_timer);
		float test = dTime;
		m_timer += dTime * m_moveTimePerSec;
		DEBUG_LOG(L"timer", m_timer);
		if (m_timer > 1)
		{
			m_isPlay = m_isLoop;
			m_timer = 0;
		}
	}

	

}

void MoveBySpline::ClearPoints()
{
	m_spline.DeletePoints();
}

void MoveBySpline::Play()
{
	m_isPlay = true;
	m_timer = 0;
}

MoveBySpline* MoveBySpline::AddSplinePoint(const Vector3 & _point)
{
	m_spline.AddPoint(_point);
	return this;
}
