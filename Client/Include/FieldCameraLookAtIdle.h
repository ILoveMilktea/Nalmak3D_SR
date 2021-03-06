#pragma once
#include "IState.h"
class FieldCameraLookAtIdle :
	public IState
{
public:
	FieldCameraLookAtIdle();
	virtual ~FieldCameraLookAtIdle();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

