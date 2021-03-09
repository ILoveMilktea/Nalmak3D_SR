#pragma once
#include "IState.h"
class State_Camera_Wait :
	public IState
{
public:
	State_Camera_Wait();
	~State_Camera_Wait();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

