#pragma once
#ifndef __SCRIPTEND_H__
#define __SCRIPTEND_H__

#include "IState.h"
class Scripter;
class ScriptEnd :
	public IState
{
public:
	ScriptEnd();
	~ScriptEnd();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	Scripter* m_scripter;
};


#endif // !__SCRIPTEND_H__