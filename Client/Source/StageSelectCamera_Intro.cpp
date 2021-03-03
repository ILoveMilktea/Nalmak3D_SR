#include "stdafx.h"
#include "StageSelectCamera_Intro.h"
#include "StageSelectCamera.h"

StageSelectCamera_Intro::StageSelectCamera_Intro()
{
}


StageSelectCamera_Intro::~StageSelectCamera_Intro()
{
}

void StageSelectCamera_Intro::Initialize()
{
	m_stageCam = GetComponent<StageSelectCamera>();
}

void StageSelectCamera_Intro::EnterState()
{
	m_stageCam->SetXMyAngle(20);
	m_stageCam->SetDistance(-15);
	m_stageCam->SetFollowSpeed(3);
	m_stageCam->SetRotateSpeed(3);
	m_stageCam->SetLookSpeed(3);
	m_stageCam->SetAxisTargetPos(Vector3(0, 30, 0));

}

void StageSelectCamera_Intro::UpdateState()
{
	
	if (m_stageCam->IsNearToTarget())
	{
		SetState(L"idle");
		return;
	}

}

void StageSelectCamera_Intro::ExitState()
{
}
