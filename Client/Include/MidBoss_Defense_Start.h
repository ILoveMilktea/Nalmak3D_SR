#pragma once
#include "IState.h"
class MidBoss_Defense_Start :
	public IState
{
public:
	MidBoss_Defense_Start();
	~MidBoss_Defense_Start();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

