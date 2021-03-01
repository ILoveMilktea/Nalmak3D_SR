#pragma once
#include "IState.h"


class Enemy_Hold :
	public IState
{
public:
	Enemy_Hold();
	virtual ~Enemy_Hold();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:
	class Enemy* m_pEnemy = nullptr;

	bool	m_bAvoid = false;
	float	m_fAvoidDelta = 0.f;

};

