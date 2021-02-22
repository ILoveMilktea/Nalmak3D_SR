#pragma once
#include "IState.h"
class Enemy_Chase :
	public IState
{
public:
	Enemy_Chase();
	virtual ~Enemy_Chase();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

