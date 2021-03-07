#pragma once
#include "IState.h"
class MidBoss_Rotate180 :
	public IState
{
public:
	MidBoss_Rotate180();
	~MidBoss_Rotate180();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

