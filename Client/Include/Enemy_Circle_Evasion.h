#pragma once
#include "IState.h"
#include "Enemy_Evasion.h"
class Circle_Evasion :
	public Enemy_Evasion
{
public:
	Circle_Evasion();
	virtual ~Circle_Evasion();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:
	float		m_fStateDelta = 0.f;

	float		m_fShootDelta = 0.f;
	int			m_iCount = 0;
	float		m_fAngle = 0.f;
	Quaternion	m_qOrigin;
};

