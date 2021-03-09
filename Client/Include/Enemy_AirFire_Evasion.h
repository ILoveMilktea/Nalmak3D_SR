#pragma once
#include "IState.h"
#include "Enemy_Evasion.h"
class AirFire_Evasion :
	public Enemy_Evasion
{
public:
	AirFire_Evasion();
	virtual ~AirFire_Evasion();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:
	void Show_TargetPos();
public:

private:
	GameObject*		m_pPlayer = nullptr;

	//Vector3			m_vRandPos = { 0.f, 0.f, 0.f }; 
	Vector3			m_vDestPos = { 0.f, 0.f, 0.f };
	

	float			m_fShootDelta = 0.f;
	float			m_fBurstDelta = 0.f;

	int				m_iCount = 0;
	
	vector<GameObject*> m_vTarget_Plane;
};

