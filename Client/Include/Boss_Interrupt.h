#pragma once
#include "IState.h"
class Boss_Interrupt :
	public IState
{
public:
	Boss_Interrupt();
	virtual ~Boss_Interrupt();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:

};

