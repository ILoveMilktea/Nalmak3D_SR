#pragma once
#include "IState.h"
class Player_Boss_Enter :
	public IState
{
public:
	Player_Boss_Enter();
	virtual ~Player_Boss_Enter();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:
	bool	m_bBackStep = false;

};

