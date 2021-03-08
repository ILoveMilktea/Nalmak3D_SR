#pragma once
#include "IState.h"
class Player_Evasion_Exit :
	public IState
{
public:
	Player_Evasion_Exit();
	virtual ~Player_Evasion_Exit();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:
	void CalcDir();
	void RotReset();

private:
	float m_fSpd = 0.f;
	Vector3 m_vDir = { 0.f,0.f,0.f };
	//must be init setting vaulue upper 0.1
	bool	m_bNext = false;
};

