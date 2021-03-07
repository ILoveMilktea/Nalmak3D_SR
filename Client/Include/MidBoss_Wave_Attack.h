#pragma once
#include "IState.h"
class MidBoss_Wave_Attack :
	public IState
{
public:
	MidBoss_Wave_Attack();
	~MidBoss_Wave_Attack();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

	void WaveAttack();

private:
	float g_waveAngle;
	float g_waveTerm;
	int g_waveAttackCount;
	int g_waveBulletCount;

	int m_curWaveAttackIndex;
	float m_waveTimer;
};

