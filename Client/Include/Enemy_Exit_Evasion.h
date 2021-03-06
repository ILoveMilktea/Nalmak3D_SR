#pragma once
#include "IState.h"
class Exit_Evasion :
	public IState
{
public:
	Exit_Evasion();
	~Exit_Evasion();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:
	void Turn();
	void Go_Straight();

	void Accelerate();
	void Destory();

private:
	float	m_fSpd = 0.f;
	int		m_iDir;
	int		m_iRotSpd;
	float	m_fRotDelta = 0.f;
	float		m_fRotTime = 0.f;
};

