#include "stdafx.h"
#include "StageSelectCamera_Idle.h"
#include "MoveBySpline.h"

StageSelectCamera_Idle::StageSelectCamera_Idle()
{
}


StageSelectCamera_Idle::~StageSelectCamera_Idle()
{
}

void StageSelectCamera_Idle::Initialize()
{
}

void StageSelectCamera_Idle::EnterState()
{
}

void StageSelectCamera_Idle::UpdateState()
{
	//m_transform->LookAt({ 0,55,55 }, 1.5f);
	//m_transform->SetRotationZ(0);

	if (GetComponent<MoveBySpline>()->IsPlaying())
		return;


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
