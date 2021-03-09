#pragma once
#include "IState.h"
class MidBoss_Laser_Fire :
	public IState
{
public:
	MidBoss_Laser_Fire();
	~MidBoss_Laser_Fire();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

	void CreateLaser(Vector3 _startPoint, Vector3 _endPoint, float width);

private:
	float g_fireDuration;
	float m_timer;

	Transform* m_bulletproof[4];

	GameObject* m_mainLaser;
	GameObject* m_subLaser[4];
};

