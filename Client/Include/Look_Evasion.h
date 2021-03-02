#pragma once
#include "IState.h"
class Look_Evasion :
	public IState
{
public:
	Look_Evasion();
	virtual ~Look_Evasion();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

public:

private:
	GameObject* m_pPlayer = nullptr;
		
	Vector3		m_vDir;

	float		m_fLookDelta = 0.f;
	float		m_fFpmDelta = 0.f;
	float		m_fFpm = 120.f;
};

