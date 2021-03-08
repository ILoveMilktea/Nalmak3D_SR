#pragma once
#include "IState.h"
class State_Camera_Evasion :
	public IState
{
public:
	State_Camera_Evasion();
	~State_Camera_Evasion();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

