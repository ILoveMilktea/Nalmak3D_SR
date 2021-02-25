#pragma once
#include "IState.h"
class Enemy_Death :
	public IState
{
public:
	Enemy_Death();
	virtual ~Enemy_Death();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:
};

