#pragma once
#include "IState.h"
class FieldCameraStartState :
	public IState
{
public:
	FieldCameraStartState();
	virtual ~FieldCameraStartState();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	class FieldCameraInfo* m_FieldCam;
	Transform* m_player;
	float m_dampingSpeed = 0.f;
	float m_dampingAccel = 0.f;
	int  m_maximumTime = 0.f;
	InputManager* m_inputMgr;

};
