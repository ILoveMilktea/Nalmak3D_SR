#pragma once
#ifndef __IANIMATION_H__
#define __IANIMATION_H__

#include "Nalmak_Include.h"

class TimeManager;
class NALMAK_DLL IAnimation
{
public:
	IAnimation();
	virtual ~IAnimation() = default;

public:
	virtual void Start_Animation() = 0;
	virtual bool Play_CurrentAnimation() = 0;
	virtual void End_Animation() = 0;

protected:
	TimeManager* m_timeManager;
	bool m_isPlay;
	float m_playTimer;
	float m_playDuration;
};
#endif // !__IANIMATION_H__



