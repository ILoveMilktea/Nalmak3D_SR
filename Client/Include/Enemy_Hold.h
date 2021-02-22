#pragma once
#include "IState.h"
class Enemy_Hold :
	public IState
{
public:
	Enemy_Hold();
	virtual ~Enemy_Hold();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

