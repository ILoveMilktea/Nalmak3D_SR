#pragma once
#include "IState.h"
class DogFight_Stage2_4 :
	public IState
{
public:
	DogFight_Stage2_4();
	virtual ~DogFight_Stage2_4();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

