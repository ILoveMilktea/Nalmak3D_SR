#include "stdafx.h"
#include "..\Include\FieldCameraSmoothFollowState.h"
#include "SmoothFollow.h"
#include "FieldCameraInfo.h"

FieldCameraSmoothFollowState::FieldCameraSmoothFollowState()
{
}


FieldCameraSmoothFollowState::~FieldCameraSmoothFollowState()
{
}

void FieldCameraSmoothFollowState::Initialize()
{
	m_inputMgr = InputManager::GetInstance();
}

void FieldCameraSmoothFollowState::EnterState()
{

	m_FieldCam = GetComponent<FieldCameraInfo>();

	/*m_FieldCam->SetXMyAngle(0.f);
	m_FieldCam->SetYMyAngle(-90.f);
	m_FieldCam->SetZMyAngle(0.f);


	m_FieldCam->SetXAxisAngle(0);
	m_FieldCam->SetYAxisAngle(90.f);
	m_FieldCam->SetZAxisAngle(0);

	m_FieldCam->RotateXAxisAngle(0.f);
	m_FieldCam->RotateYAxisAngle(0.f);


	m_FieldCam->SetDistance(20);
	m_FieldCam->SetFollowSpeed(1.f);
	m_FieldCam->SetRotateSpeed(1.f);
	m_FieldCam->SetLookSpeed(1.f);*/

	m_gameObject->GetComponent<FieldCameraInfo>()->SetActive(false);
	m_gameObject->GetComponent<SmoothFollow>()->SetActive(true);

	
}

void FieldCameraSmoothFollowState::UpdateState()
{
	if (m_inputMgr->GetKeyDown(KEY_STATE::KEY_STATE_0))
	{
		m_gameObject->GetComponent<StateControl>()->SetState(L"CameraStart");
	}
}

void FieldCameraSmoothFollowState::ExitState()
{
	m_gameObject->GetComponent<SmoothFollow>()->SetActive(false);
	m_gameObject->GetComponent<FieldCameraInfo>()->SetActive(true);

}