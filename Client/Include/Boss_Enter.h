#pragma once
#include "IState.h"
class Boss_Enter :
	public IState
{
public:
	Boss_Enter();
	virtual ~Boss_Enter();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:
	//bool m_
};

