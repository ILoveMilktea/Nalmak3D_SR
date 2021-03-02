#pragma once
#include "IState.h"
class CrossFire_Evasion :
	public IState
{
public:
	CrossFire_Evasion();
	virtual ~CrossFire_Evasion();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

public:

private:
	//float	m_fDir = 0.f;
	float	m_fSpd = 15.f;

	float	m_fFpm = 180.f;
	float	m_fFpmDelta = 0.f;
	int		m_iCount = 0;


	float	m_fShootAngle = 225.f;
	bool	m_bAngleAdd = false;


};

