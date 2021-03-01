#include "stdafx.h"
#include "StageSelectCamera_Stage1.h"
#include "MoveBySpline.h"

StageSelectCamera_Stage1::StageSelectCamera_Stage1()
{
}


StageSelectCamera_Stage1::~StageSelectCamera_Stage1()
{
}

void StageSelectCamera_Stage1::Initialize()
{
}

void StageSelectCamera_Stage1::EnterState()
{
	auto spline = GetComponent<MoveBySpline>();
	spline->ClearPoints();

	spline->AddSplinePoint({ 25, 0,75 });
	spline->AddSplinePoint({ 0, 60,50 });
	spline->AddSplinePoint({ -25,30,25 });
	spline->AddSplinePoint({ -50,20,0 });
	spline->AddSplinePoint({ -75,50,-25 });
	spline->Play();
}

void StageSelectCamera_Stage1::UpdateState()
{
	//m_transform->LookAt({ -50,15,5 }, 1.5f);
	//m_transform->SetRotationZ(0);

	if (GetComponent<MoveBySpline>()->IsPlaying())
		return;


	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_ESC))
	{
		SetState(L"idle");
		return;
	}
}

void StageSelectCamera_Stage1::ExitState()
{
	auto spline = GetComponent<MoveBySpline>();
	spline->ClearPoints();

	spline->AddSplinePoint({ -75,50,-25 });
	spline->AddSplinePoint({ -50,20,0 });
	spline->AddSplinePoint({ -25,30,25 });
	spline->AddSplinePoint({ 0, 60,50 });
	spline->AddSplinePoint({ 25, 0,75 });
	spline->Play();
}
