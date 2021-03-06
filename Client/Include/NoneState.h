#pragma once
#include "IState.h"
class NoneState :
	public IState
{
public:
	NoneState();
	virtual ~NoneState();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

