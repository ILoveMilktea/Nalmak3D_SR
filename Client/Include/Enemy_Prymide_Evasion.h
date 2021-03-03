#pragma once
#include "IState.h"
#include "Enemy_Evasion.h"
class Prymide_Evasion :
	public Enemy_Evasion
{
public:
	Prymide_Evasion();
	virtual ~Prymide_Evasion();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:
	float	m_fShootDelta = 0.f;
	float	m_fBurstDelta = 0.f;
	int		m_iCount = 0;

	float		m_fAngle[5] = {30.f, 15.f, 0.f, -15.f, -30.f};
	Quaternion	m_qOrigin;

};

