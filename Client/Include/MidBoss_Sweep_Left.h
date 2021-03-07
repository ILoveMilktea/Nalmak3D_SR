#pragma once
#include "IState.h"
class MidBoss_Sweep_Left :
	public IState
{
public:
	MidBoss_Sweep_Left();
	~MidBoss_Sweep_Left();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

	void SweepAttack();

private:
	float g_patternDuration;
	float g_patternTimer;
	float g_moveSpeed;
	float g_moveRange;

	float m_lerpTimer;
	float m_lerpDuration;

	Vector3 m_startPos;

private:
	float g_fireTimer;
	float g_fireTerm;
	int g_branchCount;

	float m_fireTerm;
};

