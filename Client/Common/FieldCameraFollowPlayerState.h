#pragma once
#include "IState.h"
class FieldCameraFollowPlayerState :
	public IState
{
public:
	FieldCameraFollowPlayerState();
	virtual ~FieldCameraFollowPlayerState();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	GameObject* m_lookAtTarget;
	InputManager* m_inputMgr;
};

