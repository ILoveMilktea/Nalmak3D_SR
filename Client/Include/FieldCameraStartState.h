#pragma once
#include "IState.h"
class FieldCameraStartState :
	public IState
{
public:
	FieldCameraStartState();
	virtual ~FieldCameraStartState();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	class FieldCameraInfo* m_FieldCam;
	Transform* m_player;
	float m_dampingSpeed = 0.f;
	float m_dampingAccel = 0.f;
	int  m_maximumTime = 0;
	InputManager* m_inputMgr;

};

