#pragma once
#include "IState.h"
class PlayerAttak :
	public IState
{
public:
	PlayerAttak();
	virtual ~PlayerAttak();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

