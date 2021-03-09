#pragma once
#include "IState.h"
class Enemy_Evasion :
	public IState
{
public:
	Enemy_Evasion();
	virtual ~Enemy_Evasion();

	virtual void Initialize() = 0;
	virtual void EnterState()  = 0;
	virtual void UpdateState() =0;
	virtual void ExitState() =0;

public:
	void Exit(); 
public:
	void SetLifeTime(float time) { m_fLifeTime = time; }

private:
	float	m_fLifeTime;
	float	m_fExitDelta = 0.f;
};

