#pragma once
#include "IState.h"
class Player_Evasion_Move :
	public IState
{
public:
	Player_Evasion_Move();
	virtual ~Player_Evasion_Move();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:
	
public:
	void Lean(int _a);

private:
	float m_fRotZ = 0.f; 

	float	 m_fClamp_x;
	float	 m_fClamp_y;
	
};

