#pragma once
#include "IState.h"
class MidBoss_Laser_Siege :
	public IState
{
public:
	MidBoss_Laser_Siege();
	~MidBoss_Laser_Siege();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	Transform* m_rotatePivot;
	Vector3 m_startPosition;

	Quaternion m_startRot;
	Quaternion m_siegeRot;

	float m_timer;
	float g_siegeDuration;
};

