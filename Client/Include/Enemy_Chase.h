#pragma once
#include "IState.h"
class Enemy_Chase :
	public IState
{
public:
	Enemy_Chase();
	virtual ~Enemy_Chase();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:


private:
	class Enemy* m_pEnemy;

	bool	m_bAvoid = false;
	float	m_fAvoidDelta = 0.f;
};

