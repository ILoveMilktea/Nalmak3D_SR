#include "stdafx.h"
#include "StageSelectCamera_Intro.h"
#include "MoveBySpline.h"

StageSelectCamera_Intro::StageSelectCamera_Intro()
{
}


StageSelectCamera_Intro::~StageSelectCamera_Intro()
{
}

void StageSelectCamera_Intro::Initialize()
{
}

void StageSelectCamera_Intro::EnterState()
{
	auto spline = GetComponent<MoveBySpline>();
	spline->ClearPoints();
	spline->AddSplinePoint({ 0,50,-100 });
	spline->AddSplinePoint({ 0,100,-50 });
	spline->AddSplinePoint({ 0,50,0 });
	spline->AddSplinePoint({ 0,60,50 });
	spline->AddSplinePoint({ 0, 0,100 });
	spline->Play();

}

void StageSelectCamera_Intro::UpdateState()
{
	/*m_transform->LookAt({ 0,35,60 }, 1.5f);
	m_transform->SetRotationZ(0);*/

	if (!GetComponent<MoveBySpline>()->IsPlaying())
	{
		SetState(L"idle");
		return;
	}

}

void StageSelectCamera_Intro::ExitState()
{
}
