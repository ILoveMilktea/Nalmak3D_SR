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
	

	m_inputMgr = InputManager::GetInstance();
}

void FieldCameraStartState::EnterState()
{
	//m_gameObject->DeleteComponent<FieldCameraInfo>();
	//m_gameObject->AddComponent<FieldCameraInfo>();

	m_FieldCam = GetComponent<FieldCameraInfo>();
	/*m_FieldCam->SetTarget(m_gameObject->GetTransform());*/
	m_player = PlayerInfoManager::GetInstance()->GetPlayer()->GetTransform();
	m_FieldCam->SetAxisTargetPos(m_player->GetWorldPosition() + Vector3(0.f,0.f, 2.f));



	m_FieldCam->SetXMyAngle(0.f);
	m_FieldCam->SetYMyAngle(0.f);
	m_FieldCam->SetZMyAngle(0.f);


	m_FieldCam->SetXAxisAngle(20.f);
	m_FieldCam->SetYAxisAngle(180.f);
	m_FieldCam->SetZAxisAngle(0);

	m_FieldCam->RotateXAxisAngle(0.f);
	m_FieldCam->RotateYAxisAngle(0.f);


	m_FieldCam->SetDistance(20);
	m_FieldCam->SetFollowSpeed(3.f);
	m_FieldCam->SetRotateSpeed(1.f);
	m_FieldCam->SetLookSpeed(1.f);


}

void FieldCameraStartState::UpdateState()
{

	m_dampingAccel = Nalmak_Math::Lerp(m_dampingAccel, 1.f, dTime * 50);


	if (m_FieldCam->GetDistance() >= 5.5f)
	{
		m_FieldCam->SetAxisTargetPos(m_player->GetWorldPosition() + Vector3(0.f, 0.f, 2.f));
		
		m_dampingSpeed += m_dampingAccel;
		m_FieldCam->AddDistance(-m_dampingSpeed * dTime);
	}
	else
	{
		m_FieldCam->SetAxisTargetPos(m_player->GetWorldPosition() + Vector3(0.f, 0.f, 3.f));
		m_FieldCam->RotateYAxisAngle(15.f);
	}


	if (m_FieldCam->GetYAxisAngle() >= 180.f + PI2)
	{
		SetState(L"CameraNearEnemy");
		return;
	}

	if (m_inputMgr->GetKeyDown(KEY_STATE::KEY_STATE_0))
	{
		SetState(L"CameraNearEnemy");
		return;
	}


	DEBUG_LOG(L"distance", m_FieldCam->GetDistance());
	DEBUG_LOG(L"½ÃÀÛ", m_FieldCam->GetYAxisAngle());
}

void FieldCameraStartState::ExitState()
{
}
