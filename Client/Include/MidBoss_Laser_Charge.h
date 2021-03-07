#pragma once
#include "IState.h"
class MidBoss_Laser_Charge :
	public IState
{
public:
	MidBoss_Laser_Charge();
	~MidBoss_Laser_Charge();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	float g_chargeDuration;
	float m_timer;
};

