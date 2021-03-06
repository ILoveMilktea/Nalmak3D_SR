#pragma once
#ifndef __ROTATEANIMATION_H__
#define __ROTATEANIMATION_H__

#include "IAnimation.h"

class NALMAK_DLL RotateAnimation :
	public IAnimation
{
public:
	RotateAnimation();
	~RotateAnimation();

public:
	virtual void Start_Animation() override;
	virtual bool Play_CurrentAnimation() override;
	virtual void End_Animation() override;

	virtual void Play_Lerp() override;
	virtual void Play_Custom() override;


};


#endif // !__ROTATEANIMATION_H__
