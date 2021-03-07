#pragma once
#include "IState.h"
class MidBoss_MoveToCenter :
	public IState
{
public:
	MidBoss_MoveToCenter();
	~MidBoss_MoveToCenter();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	Vector3 m_startPosition;
	Vector3 m_centerPosition;
	
	float m_lerpTimer;
	float m_lerpDuration;
};

