#include "stdafx.h"
#include "..\Include\GarageSceneCameraIntro.h"
#include "GarageSceneCameraInfo.h"

GarageSceneCameraIntro::GarageSceneCameraIntro()
{
}


GarageSceneCameraIntro::~GarageSceneCameraIntro()
{
}

void GarageSceneCameraIntro::Initialize()
{
	m_player = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER)->GetTransform();

	m_garageCam = GetComponent<GarageSceneCameraInfo>();
	
	

}

void GarageSceneCameraIntro::EnterState()
{
	m_garageCam->SetXMyAngle(20);
	m_garageCam->SetDistance(-15);
	m_garageCam->SetFollowSpeed(3);
	m_garageCam->SetRotateSpeed(3);
	m_garageCam->SetLookSpeed(3);

}

void GarageSceneCameraIntro::UpdateState()
{
	if (abs(m_garageCam->GetTransform()->position.z - m_garageCam->GetDistance()) < 0.1f)
	{
		SetState(L"autoRotate");
		return;
	}
}

void GarageSceneCameraIntro::ExitState()
{
}
