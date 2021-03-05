#include "stdafx.h"
#include "..\Include\FieldCameraStartState.h"
#include "FieldCameraInfo.h"

//test
#include "GarageSceneCameraInfo.h"
FieldCameraStartState::FieldCameraStartState()
{
}


FieldCameraStartState::~FieldCameraStartState()
{
}

void FieldCameraStartState::Initialize()
{
	


}

void FieldCameraStartState::EnterState()
{
	m_gameObject->DeleteComponent<FieldCameraInfo>();
	m_gameObject->AddComponent<GarageSceneCameraInfo>();

	m_FieldCam = GetComponent<GarageSceneCameraInfo>();
	/*m_FieldCam->SetTarget(m_gameObject->GetTransform());*/
	m_FieldCam->SetYMyAngle(90.f);
	m_FieldCam->SetYAxisAngle(90.f);
	m_FieldCam->SetDistance(20);
	m_FieldCam->SetFollowSpeed(1.f);
	m_FieldCam->SetRotateSpeed(1.f);
	m_FieldCam->SetLookSpeed(1.f);
}

void FieldCameraStartState::UpdateState()
{
	//m_FieldCam->SetAxisTargetPos({ 0.f, 0.f, 10.f });

}

void FieldCameraStartState::ExitState()
{
}
