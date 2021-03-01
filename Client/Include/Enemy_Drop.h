#pragma once
#include "IState.h"
class Enemy_Drop :
	public IState
{
public:
	Enemy_Drop();
	virtual ~Enemy_Drop();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:
	class Enemy* m_pEnemy = nullptr;

	bool		m_bAvoid = false;
	bool		m_bRandMove = false;
	bool		m_bDive = false;
	bool		m_bSoar = false;

	float		m_fAvoidDelta = 0.f;

};

