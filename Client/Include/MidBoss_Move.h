#pragma once
#include "IState.h"
class MidBoss_Move :
	public IState
{
public:
	MidBoss_Move();
	~MidBoss_Move();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

