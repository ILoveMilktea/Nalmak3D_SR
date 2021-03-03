#include "stdafx.h"
#include "StageSelectCamera_Idle.h"
#include "StageSelectCamera.h"

StageSelectCamera_Idle::StageSelectCamera_Idle()
{
}


StageSelectCamera_Idle::~StageSelectCamera_Idle()
{
}

void StageSelectCamera_Idle::Initialize()
{
	m_stageCam = GetComponent<StageSelectCamera>();
}

void StageSelectCamera_Idle::EnterState()
{
	m_stageCam->SetXMyAngle(30);
	m_stageCam->SetDistance(-35);
	m_stageCam->SetFollowSpeed(3);
	m_stageCam->SetRotateSpeed(3);
	m_stageCam->SetLookSpeed(3);
	m_stageCam->RotateYAxisAngle(0);
	m_stageCam->SetAxisTargetPos(Vector3(10, 20, 50));
}

void StageSelectCamera_Idle::UpdateState()
{

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_A))
	{
		SetState(L"stage1");
		return;
	}
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_D))
	{
		SetState(L"stage2");
		return;
	}
}

void StageSelectCamera_Idle::ExitState()
{
}
