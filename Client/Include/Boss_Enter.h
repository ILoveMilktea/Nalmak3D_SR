#pragma once
#include "IState.h"
class Boss_Enter :
	public IState
{
public:
	Boss_Enter();
	virtual ~Boss_Enter();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:
	//bool m_
};

