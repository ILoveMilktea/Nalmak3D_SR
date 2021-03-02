#pragma once
#include "IState.h"
class PlayerNone :
	public IState
{
public:
	PlayerNone();
	virtual ~PlayerNone();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

