#include "..\Include\ColorAnimation.h"



ColorAnimation::ColorAnimation()
{
}


ColorAnimation::~ColorAnimation()
{
}

void ColorAnimation::Start_Animation()
{
	IAnimation::Start_Animation();
}

bool ColorAnimation::Play_CurrentAnimation()
{
	IAnimation::Play_CurrentAnimation();

	return true;
}

void ColorAnimation::End_Animation()
{
	IAnimation::End_Animation();
}

void ColorAnimation::Play_ChangeRed()
{
}

void ColorAnimation::Play_ChangeGreen()
{
}

void ColorAnimation::Play_ChangeBlue()
{
}

void ColorAnimation::Play_FadeIn()
{
}

void ColorAnimation::Play_FadeOut()
{
}

void ColorAnimation::Play_FadeCustom()
{
}
