#pragma once
#include "IState.h"
class MidBoss_Appear :
	public IState
{
public:
	MidBoss_Appear();
	~MidBoss_Appear();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	float m_lerpTimer;
	float m_lerpDuration;

	Vector3 m_startPosition;
	Vector3 m_centerPosition;
};

