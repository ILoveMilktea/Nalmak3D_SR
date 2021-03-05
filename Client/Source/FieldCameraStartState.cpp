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
	//m_gameObject->DeleteComponent<FieldCameraInfo>();
	//m_gameObject->AddComponent<FieldCameraInfo>();

	m_FieldCam = GetComponent<FieldCameraInfo>();
	/*m_FieldCam->SetTarget(m_gameObject->GetTransform());*/

	m_FieldCam->SetAxisTargetPos(PlayerInfoManager::GetInstance()->GetPlayer()->GetTransform()->GetWorldPosition());


	m_FieldCam->SetXMyAngle(0.f);
	m_FieldCam->SetYMyAngle(0.f);
	m_FieldCam->SetZMyAngle(0.f);


	m_FieldCam->SetXAxisAngle(0);
	m_FieldCam->SetYAxisAngle(180.f);
	m_FieldCam->SetZAxisAngle(0);

	m_FieldCam->RotateXAxisAngle(0.f);
	m_FieldCam->RotateYAxisAngle(0.f);


	m_FieldCam->SetDistance(20);
	m_FieldCam->SetFollowSpeed(3.f);
	m_FieldCam->SetRotateSpeed(1.f);
	m_FieldCam->SetLookSpeed(1.f);

	m_player = PlayerInfoManager::GetInstance()->GetPlayer()->GetTransform();
}

void FieldCameraStartState::UpdateState()
{

	DEBUG_LOG(L"½ÃÀÛ", L"dd");
//	m_FieldCam->SetAxisTargetPos(m_player->position);
	//m_FieldCam->SetAxisTargetPos({ 0.f, 0.f, 10.f });
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_C))
	{
		SetState(L"CameraFollow");
	}
}

void FieldCameraStartState::ExitState()
{
}
