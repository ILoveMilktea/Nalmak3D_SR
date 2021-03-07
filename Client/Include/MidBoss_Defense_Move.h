#pragma once
#include "IState.h"
class MidBoss_Defense_Move :
	public IState
{
public:
	MidBoss_Defense_Move();
	~MidBoss_Defense_Move();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

