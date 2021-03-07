#pragma once
#include "IState.h"
class MidBoss_Idle :
	public IState
{
public:
	enum PATTERN { WAVE, SWEEP, HOMING, DEFENSE };

public:
	MidBoss_Idle();
	~MidBoss_Idle();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	int g_patternIndex;

	float m_stateTimer;
	float m_stateTerm;
};

