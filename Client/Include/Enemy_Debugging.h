#pragma once
#include "IState.h"
class Enemy_Debugging :
	public IState
{
public:
	Enemy_Debugging();
	virtual ~Enemy_Debugging();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

private:
	class Enemy* m_pEnemy = nullptr;
};

