#pragma once
#include "IState.h"
class Boss_Interrupt :
	public IState
{
public:
	Boss_Interrupt();
	virtual ~Boss_Interrupt();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:

};

