#include "..\Include\RotateAnimation.h"



RotateAnimation::RotateAnimation()
{
}


RotateAnimation::~RotateAnimation()
{
}

void RotateAnimation::Start_Animation()
{
	IAnimation::Start_Animation();
}

bool RotateAnimation::Play_CurrentAnimation()
{
	if (!IAnimation::Play_CurrentAnimation())
		return false;

	return true;
}

void RotateAnimation::End_Animation()
{
	IAnimation::End_Animation();
}

void RotateAnimation::Play_Lerp()
{
}

void RotateAnimation::Play_Custom()
{
}
