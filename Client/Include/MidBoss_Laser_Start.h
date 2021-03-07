#pragma once
#include "IState.h"

// start
// -> movetocenter + Setrotate
// -> DetachPlates
// -> charge
// -> fire
// -> discharge
// -> AttachPlates

class MidBoss_Laser_Start :
	public IState
{
public:
	MidBoss_Laser_Start();
	~MidBoss_Laser_Start();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

