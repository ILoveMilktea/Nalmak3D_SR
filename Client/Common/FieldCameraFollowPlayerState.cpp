#include "stdafx.h"
#include "FieldCameraFollowPlayerState.h"
#include "SmoothFollow.h"

FieldCameraFollowPlayerState::FieldCameraFollowPlayerState()
{
}


FieldCameraFollowPlayerState::~FieldCameraFollowPlayerState()
{
}

void FieldCameraFollowPlayerState::Initialize()
{
	m_inputMgr = InputManager::GetInstance();

}

void FieldCameraFollowPlayerState::EnterState()
{
	m_lookAtTarget = PlayerInfoManager::GetInstance()->GetPlayer();
	SmoothFollow::Desc followInfo;
	followInfo.toTarget = m_lookAtTarget;
	m_gameObject->AddComponent<SmoothFollow>(&followInfo);
}

void FieldCameraFollowPlayerState::UpdateState()
{
	// Á¶°Ç
	if (m_inputMgr->GetKeyDown(KEY_STATE::KEY_STATE_0))
	{
		m_gameObject->GetComponent<StateControl>()->SetState(L"cameraZoomIn");
	}
}

void FieldCameraFollowPlayerState::ExitState()
{
	m_gameObject->DeleteComponent<SmoothFollow>();
}
