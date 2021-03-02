#include "..\Include\ScaleAnimation.h"



ScaleAnimation::ScaleAnimation()
{
}


ScaleAnimation::~ScaleAnimation()
{
}

void ScaleAnimation::Start_Animation()
{
	IAnimation::Start_Animation();
}

bool ScaleAnimation::Play_CurrentAnimation()
{
	IAnimation::Play_CurrentAnimation();

	return true;
}

void ScaleAnimation::End_Animation()
{
	IAnimation::End_Animation();
}

void ScaleAnimation::Play_ChangeScaleX()
{
}

void ScaleAnimation::Play_ChangeScaleY()
{
}

void ScaleAnimation::Play_ChangeScaleZ()
{
}

void ScaleAnimation::Play_ScaleCustom()
{
}
