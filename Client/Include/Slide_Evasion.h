#pragma once
#include "IState.h"
class Slide_Evasion :
	public IState
{
public:
	Slide_Evasion();
	virtual ~Slide_Evasion();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public: 


public:

	
public:

	
private:
	int		m_iDirection = 0;

	float	m_fSpd = 15.f;
	float	m_fFpm = 120.f;
	float	m_fFpmDelta = 0.f;

};

