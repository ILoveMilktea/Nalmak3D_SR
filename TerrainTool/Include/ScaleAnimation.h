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

	virtual void Play_Lerp() override;
	virtual void Play_Custom() override;


public:
	void SetStart();
	void SetStartScale(Vector3 _start);
	void SetDestScale(Vector3 _dest) { m_destScale = _dest; }

private:
	Vector3 m_startScale;
	Vector3 m_destScale;
};


#endif // !__SCALEANIMATION_H__
