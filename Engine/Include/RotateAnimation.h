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

	virtual bool Play_RotateX();
	virtual bool Play_RotateY();
	virtual bool Play_RotateZ();
	virtual bool Play_RotateCustom();

};


#endif // !__ROTATEANIMATION_H__
