#pragma once
#include "IState.h"
class Player_Evasion_Enter :
	public IState
{
public:
	Player_Evasion_Enter();
	virtual ~Player_Evasion_Enter();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:
	void Decelerate();
private:
	float m_fSpd = 0.f;
	//must be init setting vaulue upper 0.1


};

