#pragma once
#include "IState.h"
class FieldCameraSmoothFollowState :
	public IState
{
public:
	FieldCameraSmoothFollowState();
	virtual ~FieldCameraSmoothFollowState();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	InputManager* m_inputMgr;
	GameObject* m_lookAtTarget;
};

