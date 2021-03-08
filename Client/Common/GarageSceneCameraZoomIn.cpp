#include "stdafx.h"
#include "GarageSceneCameraZoomIn.h"
#include "GarageSceneCameraInfo.h"

GarageSceneCameraZoomIn::GarageSceneCameraZoomIn()
{
}


GarageSceneCameraZoomIn::~GarageSceneCameraZoomIn()
{
}

void GarageSceneCameraZoomIn::Initialize()
{
	m_garageCam = GetComponent<GarageSceneCameraInfo>();

}

void GarageSceneCameraZoomIn::EnterState()
{
	m_garageCam->SetXMyAngle(0);
	m_garageCam->SetXAxisAngle(-30);
	m_garageCam->SetYAxisAngle(120);
	m_garageCam->SetDistance(-5);
	m_garageCam->SetFollowSpeed(5);
	m_garageCam->SetRotateSpeed(5);
	m_garageCam->SetLookSpeed(1);
	m_garageCam->SetAxisTargetPos(Vector3(0, 1, 0));
}

void GarageSceneCameraZoomIn::UpdateState()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_A))
	{
		SetState(L"autoRotate");
		return;
	}


}

void GarageSceneCameraZoomIn::ExitState()
{

}
