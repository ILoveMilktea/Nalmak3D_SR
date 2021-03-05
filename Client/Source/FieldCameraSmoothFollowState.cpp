#include "stdafx.h"
#include "..\Include\FieldCameraSmoothFollowState.h"
#include "SmoothFollow.h"

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
	m_lookAtTarget = PlayerInfoManager::GetInstance()->GetPlayer();
	SmoothFollow::Desc followInfo;
	followInfo.toTarget = m_lookAtTarget;
	m_gameObject->AddComponent<SmoothFollow>(&followInfo);
}

void FieldCameraSmoothFollowState::UpdateState()
{
	if (m_inputMgr->GetKeyDown(KEY_STATE::KEY_STATE_0))
	{
		//m_gameObject->GetComponent<StateControl>()->SetState(L"");
	}
}

void FieldCameraSmoothFollowState::ExitState()
{
	m_lookAtTarget->DeleteComponent<SmoothFollow>();
}
