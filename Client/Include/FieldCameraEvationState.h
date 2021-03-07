#pragma once
#include "IState.h"
class FieldCameraEvationState :
	public IState
{
public:
	FieldCameraEvationState();
	virtual ~FieldCameraEvationState();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	InputManager* m_inputMgr;
	GameObject* m_lookAtTarget;
	class FieldCameraInfo* m_FieldCam;


};

