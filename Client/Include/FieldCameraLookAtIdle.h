#pragma once
#include "IState.h"
class FieldCameraLookAtIdle :
	public IState
{
public:
	FieldCameraLookAtIdle();
	virtual ~FieldCameraLookAtIdle();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

