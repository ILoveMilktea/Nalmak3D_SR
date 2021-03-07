#pragma once
#include "IState.h"

// start 
// -> go to player forward
// -> right move 
// -> left move  -> repeat until total pattern time
// -> idle


class MidBoss_Sweep_Start :
	public IState
{
public:
	MidBoss_Sweep_Start();
	~MidBoss_Sweep_Start();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

