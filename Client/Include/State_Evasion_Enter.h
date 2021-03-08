#pragma once
#include "IState.h"

class State_Evasion_Enter :
	public IState
{
public:
	State_Evasion_Enter();
	virtual ~State_Evasion_Enter();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	GameObject* m_mainCamera;
	GameObject* m_player;
};

