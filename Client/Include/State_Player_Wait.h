#pragma once
#include "IState.h"
class State_Player_Wait :
	public IState
{
public:
	State_Player_Wait();
	~State_Player_Wait();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

