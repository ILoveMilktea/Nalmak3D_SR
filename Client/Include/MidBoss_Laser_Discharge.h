#pragma once
#include "IState.h"
class MidBoss_Laser_Discharge :
	public IState
{
public:
	MidBoss_Laser_Discharge();
	~MidBoss_Laser_Discharge();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;


private:
	float g_dischargeDuration;
	float m_timer;
};

