#pragma once
#include "IState.h"
class AirFire_Evasion :
	public IState
{
public:
	AirFire_Evasion();
	virtual ~AirFire_Evasion();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:
	GameObject*		m_pPlayer = nullptr;

	//Vector3			m_vRandPos = { 0.f, 0.f, 0.f }; 
	Vector3			m_vDestPos = { 0.f, 0.f, 0.f };
	

	float			m_fShootDelta = 0.f;
	float			m_fBrustDelta = 0.f;

	int				m_iCount = 0;
	
	vector<GameObject*> Target_Plane;
};

