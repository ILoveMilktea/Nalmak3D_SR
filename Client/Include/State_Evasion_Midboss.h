#pragma once
#include "IState.h"
class State_Evasion_Midboss :
	public IState
{
public:
	State_Evasion_Midboss();
	~State_Evasion_Midboss();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	GameObject* m_midBoss;
};

