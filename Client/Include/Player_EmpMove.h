#pragma once
#include "Component.h"
class Player_EmpMove :
	public Component
{
public:
	struct Desc 
	{
		float fmaxSpd;

	};
public:
	Player_EmpMove(Desc* _desc);
	virtual ~Player_EmpMove();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;

public:
	void Go_Straight();
	void Accelerator();

	void Boom();
public:

public:

private:
	bool	m_bGo = true;
	float	m_fMaxSpd = 0.f;
	float	m_fCurSpd = 0.f;

	float	m_fEmpDelta = 0.f;

	GameObject* Pulse = nullptr;

};

