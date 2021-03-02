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
	IAnimation::Play_CurrentAnimation();

	return true;
}

void RotateAnimation::End_Animation()
{
	IAnimation::End_Animation();
}

bool RotateAnimation::Play_RotateX()
{
	return false;
}

bool RotateAnimation::Play_RotateY()
{
	return false;
}

bool RotateAnimation::Play_RotateZ()
{
	return false;
}

bool RotateAnimation::Play_RotateCustom()
{
	return false;
}
