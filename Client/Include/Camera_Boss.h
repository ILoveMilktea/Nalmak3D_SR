#pragma once
#include "IState.h"
class Camera_Boss :
	public IState
{
public:
	Camera_Boss();
	virtual ~Camera_Boss();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

