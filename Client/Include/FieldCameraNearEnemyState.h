#pragma once
#include "IState.h"
class FieldCameraNearEnemyState :
	public IState
{
public:
	FieldCameraNearEnemyState();
	virtual ~FieldCameraNearEnemyState();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	class FieldCameraInfo* m_FieldCam;
	Transform* m_NearObject;
	
	int m_randomTimer;
	int m_minRandom;
	int m_maxRandom;
	int m_rotValue;

private:
	float m_culTime;
	Vector3 m_ShakingPosition;
	float m_shakingX;
	float m_shakingY;
};

