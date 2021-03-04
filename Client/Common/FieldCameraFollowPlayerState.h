#pragma once
#include "IState.h"
class FieldCameraFollowPlayerState :
	public IState
{
public:
	FieldCameraFollowPlayerState();
	virtual ~FieldCameraFollowPlayerState();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	GameObject* m_lookAtTarget;
	InputManager* m_inputMgr;
};

