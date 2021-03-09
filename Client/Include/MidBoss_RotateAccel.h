#pragma once
#include "IState.h"
class MidBoss_RotateAccel :
	public IState
{
public:
	MidBoss_RotateAccel();
	~MidBoss_RotateAccel();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	float m_timer;
	float m_duration;
};

