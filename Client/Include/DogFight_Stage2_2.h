#pragma once
#include "IState.h"
class DogFight_Stage2_2 :
	public IState
{
public:
	DogFight_Stage2_2();
	virtual ~DogFight_Stage2_2();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

