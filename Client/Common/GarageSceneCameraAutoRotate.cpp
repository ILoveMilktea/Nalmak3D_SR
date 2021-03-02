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
	m_player = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER)->GetTransform();
	m_garageCam = GetComponent<GarageSceneCameraInfo>();



}

void GarageSceneCameraAutoRotate::EnterState()
{
	m_garageCam->SetXMyAngle(20);
	m_garageCam->SetDistance(-15);
	m_garageCam->SetFollowSpeed(3);
	m_garageCam->SetRotateSpeed(3);
	m_garageCam->SetLookSpeed(3);
	m_garageCam->SetXAxisAngle(20);
	m_garageCam->RotateYAxisAngle(5);
	m_garageCam->SetAxisTargetPos(Vector3(0, 5, 0));


}

void GarageSceneCameraAutoRotate::UpdateState()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_A))
	{
		SetState(L"zoomIn");
		return;
	}
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_RIGHT_MOUSE))
	{
		SetState(L"mouseInput");
		return;
	}
}

void GarageSceneCameraAutoRotate::ExitState()
{
	m_garageCam->RotateYAxisAngle(0);
}
