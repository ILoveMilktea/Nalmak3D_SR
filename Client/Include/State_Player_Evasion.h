#pragma once
#include "IState.h"
class State_Player_Evasion :
	public IState
{
public:
	State_Player_Evasion();
	~State_Player_Evasion();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

