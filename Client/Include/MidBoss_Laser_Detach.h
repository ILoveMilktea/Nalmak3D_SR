#pragma once
#include "IState.h"

class Enemy_BulletProof;
class MidBoss_Laser_Detach :
	public IState
{
public:
	MidBoss_Laser_Detach();
	~MidBoss_Laser_Detach();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	float g_detachDuration;
	float m_timer;

	Enemy_BulletProof* m_bulletproof[4];
};

