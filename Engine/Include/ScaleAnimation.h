#pragma once
#ifndef __SCALEANIMATION_H__
#define __SCALEANIMATION_H__

#include "IAnimation.h"

class NALMAK_DLL ScaleAnimation :
	public IAnimation
{
public:
	ScaleAnimation();
	~ScaleAnimation();

public:
	virtual void Start_Animation() override;
	virtual bool Play_CurrentAnimation() override;
	virtual void End_Animation() override;

	virtual void Play_ChangeScaleX();
	virtual void Play_ChangeScaleY();
	virtual void Play_ChangeScaleZ();
	virtual void Play_ScaleCustom();
};


#endif // !__SCALEANIMATION_H__
