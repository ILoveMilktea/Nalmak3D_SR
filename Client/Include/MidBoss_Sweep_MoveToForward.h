#pragma once
#include "IState.h"
class MidBoss_Sweep_MoveToForward :
	public IState
{
public:
	MidBoss_Sweep_MoveToForward();
	~MidBoss_Sweep_MoveToForward();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	Vector3 m_playerPos;
	Vector3 m_startPos;
	float m_lerpTimer;
	float m_lerpDuration;
};

