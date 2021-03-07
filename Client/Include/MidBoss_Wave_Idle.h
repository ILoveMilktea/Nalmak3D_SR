#pragma once
#include "IState.h"
class MidBoss_Wave_Idle :
	public IState
{
public:
	MidBoss_Wave_Idle();
	~MidBoss_Wave_Idle();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	int g_waveIndex;
	int g_waveCount;

	float g_waveIdleDuration;

	float m_idleTimer;
};

