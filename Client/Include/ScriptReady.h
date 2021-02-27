#pragma once
#ifndef __SCRIPTREADY_H__
#define __SCRIPTREADY_H__

#include "IState.h"

class Scripter;
class TimeManager;
class ScriptReady :
	public IState
{
public:
	ScriptReady();
	~ScriptReady();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
	
private:
	Scripter* m_scripter;
	TimeManager* m_timeManager;

	float m_timer;
};


#endif // !__SCRIPTREADY_H__
