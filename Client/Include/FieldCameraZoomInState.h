#pragma once
#include "IState.h"
class FieldCameraZoomInState :
	public IState
{
public:
	FieldCameraZoomInState();
	virtual ~FieldCameraZoomInState();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	GameObject * m_cameraObj;
	GameObject * m_lookAtTarget;

private:
	Vector3 m_camDir;
	Vector3 m_fromPos;
	float m_distance = 0.f;

private:
	Vector3 m_followDirection;
	Quaternion m_lookDirection;
};

