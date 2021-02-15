#pragma once
#include "IState.h"
class ShootingState :public IState
{
public:
	ShootingState();
	~ShootingState();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

