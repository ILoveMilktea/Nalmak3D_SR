#pragma once
#ifndef __COLORANIMATION_H__
#define __COLORANIMATION_H__

#include "IAnimation.h"

class NALMAK_DLL ColorAnimation :
	public IAnimation
{
public:
	ColorAnimation();
	~ColorAnimation();

public:
	virtual void Start_Animation() override;
	virtual bool Play_CurrentAnimation() override;
	virtual void End_Animation() override;

	virtual void Play_ChangeRed();
	virtual void Play_ChangeGreen();
	virtual void Play_ChangeBlue();

	virtual void Play_FadeIn();
	virtual void Play_FadeOut();
	virtual void Play_FadeCustom();

};


#endif // !__COLORANIMATION_H__
