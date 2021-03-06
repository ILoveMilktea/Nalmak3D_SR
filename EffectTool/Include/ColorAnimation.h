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

	virtual void Play_Lerp() override;
	virtual void Play_Custom() override;

public:
	void SetStartColor();
	void SetStartColor(Vector4 _color);
	void SetDestColor(Vector4 _dest) { m_destColor = _dest; }

private:
	Vector4 m_startColor;
	Vector4 m_destColor;
};


#endif // !__COLORANIMATION_H__
