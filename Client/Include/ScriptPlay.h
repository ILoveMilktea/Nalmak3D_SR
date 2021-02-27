#pragma once
#ifndef __SCRIPTPLAY_H__
#define __SCRIPTPLAY_H__

#include "IState.h"
class Scripter;
class TimeManager;
class ScriptPlay :
	public IState
{
public:
	ScriptPlay();
	~ScriptPlay();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
	
private:
	Scripter* m_scripter;
	TimeManager* m_timeManager;

	float m_timer;
};


#endif // !__SCRIPTPLAY_H__