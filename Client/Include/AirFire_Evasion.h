#pragma once
#include "IState.h"
class AirFire_Evasion :
	public IState
{
public:
	AirFire_Evasion();
	virtual ~AirFire_Evasion();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

