#pragma once
#include "IState.h"
class StageSelectCamera_Intro :
	public IState
{
public:
	StageSelectCamera_Intro();
	~StageSelectCamera_Intro();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;


};

