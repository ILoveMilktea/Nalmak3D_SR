#pragma once
#include "IState.h"
class Enemy_Drop :
	public IState
{
public:
	Enemy_Drop();
	virtual ~Enemy_Drop();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

