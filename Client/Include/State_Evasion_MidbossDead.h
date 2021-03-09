#pragma once
#include "IState.h"
class State_Evasion_MidbossDead :
	public IState
{
public:
	State_Evasion_MidbossDead();
	~State_Evasion_MidbossDead();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

