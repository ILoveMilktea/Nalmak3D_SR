#pragma once
#include "IState.h"
class Enemy_Rush :
	public IState
{
public:
	Enemy_Rush();
	virtual ~Enemy_Rush();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

