#include "stdafx.h"
#include "GarageSceneCameraAutoRotate.h"
#include "GarageSceneCameraInfo.h"

GarageSceneCameraAutoRotate::GarageSceneCameraAutoRotate()
{
}

GarageSceneCameraAutoRotate::~GarageSceneCameraAutoRotate()
{
}

void GarageSceneCameraAutoRotate::Initialize()
{
	m_garageCam = GetComponent<GarageSceneCameraInfo>();



}

void GarageSceneCameraAutoRotate::EnterState()
{
	m_garageCam->SetXMyAngle(20);
	m_garageCam->SetDistance(-5);
	m_garageCam->SetFollowSpeed(3);
	m_garageCam->SetRotateSpeed(3);
	m_garageCam->SetLookSpeed(3);
	m_garageCam->RotateYAxisAngle(5);
	m_garageCam->SetAxisTargetPos(Vector3(0, 2, 0));


}

void GarageSceneCameraAutoRotate::UpdateState()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_RIGHT_MOUSE))
	{
		SetState(L"mouseInput");
		return;
	}
	if (InputManager::GetInstance()->GetWheelScroll() != 0)
	{
		SetState(L"mouseInput");
		return;
	}
}

void GarageSceneCameraAutoRotate::ExitState()
{
	m_garageCam->RotateYAxisAngle(0);
}
