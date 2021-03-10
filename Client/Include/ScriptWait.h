#pragma once
#ifndef __SCRIPTWAIT_H__
#define __SCRIPTWAIT_H__


#include "IState.h"
class Scripter;
class ScriptWait :
	public IState
{
public:
	ScriptWait();
	~ScriptWait();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
	
public:

private:
	Scripter* m_scripter;
	TimeManager* m_timeManager;
};


#endif // !__SCRIPTWAIT_H__