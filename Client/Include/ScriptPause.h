#pragma once
#ifndef __SCRIPTPAUSE_H__
#define __SCRIPTPAUSE_H__

#include "IState.h"
class Scripter;
class ScriptPause :
	public IState
{
public:
	ScriptPause();
	~ScriptPause();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;


private:
	Scripter* m_scripter;
	TimeManager* m_timeManager;
};


#endif // !__SCRIPTPAUSE_H__