#pragma once
#include "IState.h"
class Enemy_Idle :
	public IState
{
public:
	Enemy_Idle();
	virtual ~Enemy_Idle();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:
	
public:


};

