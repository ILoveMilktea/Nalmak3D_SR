#pragma once
#include "IState.h"

class Enemy_BulletProof;
class MidBoss_Laser_Attach :
	public IState
{
public:
	MidBoss_Laser_Attach();
	~MidBoss_Laser_Attach();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	float g_attachDuration;
	float m_timer;

	Enemy_BulletProof* m_bulletproof[4];
};

