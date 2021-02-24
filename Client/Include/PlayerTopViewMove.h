#pragma once
#include "IState.h"
class PlayerTopViewMove :
	public IState
{
public:
	PlayerTopViewMove();
	virtual ~PlayerTopViewMove();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:
	void TopViewMoving();
private:

};

