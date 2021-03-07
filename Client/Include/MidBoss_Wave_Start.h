#pragma once
#include "IState.h"

// start 
// -> attack1 -> idle1
// -> attack2 -> idle2
// -> attack3 -> idle3
// -> move to center

class MidBoss_Wave_Start :
	public IState
{
public:
	MidBoss_Wave_Start();
	~MidBoss_Wave_Start();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

