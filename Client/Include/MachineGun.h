#pragma once
#include "Component.h"
class MachineGun :
	public Component
{
	
public:
	struct Desc
	{
		float	fSpd;
		int		iDmg;
	};
	
public:
	MachineGun(Desc* _desc);
	virtual ~MachineGun();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;

public:
	
private:
	float m_fSpd = 0.f;
	int m_iDamage = 0;

	float m_fDeltaTime = 0.f;
};

