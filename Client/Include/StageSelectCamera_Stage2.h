#pragma once
#include "IState.h"
class StageSelectCamera_Stage2 :
	public IState
{
public:
	StageSelectCamera_Stage2();
	~StageSelectCamera_Stage2();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

