#pragma once
#include "IState.h"
#include "Enemy_Evasion.h"
class Look_Evasion :
	public Enemy_Evasion
{
public:
	Look_Evasion();
	virtual ~Look_Evasion();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
	// Enemy_Evasion을(를) 통해 상속됨

public:

public:

public:

private:
	GameObject* m_pPlayer = nullptr;
		
	Vector3		m_vDir;

	float		m_fLookDelta = 0.f;
	
	float		m_fFpm = 60.f;
	float		m_fFpmDelta = 0.f;
	float		m_fBurstDelta = 0.f;
	
	int			m_iCount = 0;

	
};

