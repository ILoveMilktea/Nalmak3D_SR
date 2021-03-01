#include "stdafx.h"
#include "StageSelectCamera.h"
#include "StageSelectSceneManager.h"
#include "MoveBySpline.h"

StageSelectCamera::StageSelectCamera(Desc * _desc)
{
}

StageSelectCamera::~StageSelectCamera()
{
}

void StageSelectCamera::Initialize()
{
	m_spline = GetComponent<MoveBySpline>();

}

void StageSelectCamera::Update()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_A))
	{
		if (StageSelectSceneManager::GetInstance()->SelectStage(0))
		{
			MoveToPointBySpline(0);
		}
	}
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_ESC))
	{
		if (StageSelectSceneManager::GetInstance()->SelectStage(0))
		{
			MoveToPointBySpline(0);
		}
	}
}

void StageSelectCamera::MoveToPointBySpline(int _index)
{
	if (_index >= 0 && _index < m_movePoints.size())
	{
		GetComponent<MoveBySpline>()->ClearPoints();

		for (auto& point : m_movePoints[_index])
		{
			AddSplinePoint(point);
		}

		m_spline->Play();
	}
}

void StageSelectCamera::AddSplinePoint(const Vector3 & _point)
{
	m_spline->AddSplinePoint(_point);
}
