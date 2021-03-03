#pragma once
#include "Component.h"
class Enemy_AirFire_TargetPlane :
	public Component
{
public:
	struct Desc
	{
		//float fDelta = 2.f;
	};
	
public:
	Enemy_AirFire_TargetPlane(Desc* _desc);
	virtual ~Enemy_AirFire_TargetPlane();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

public:

public:

private:
	float	m_fDelta = 0.f;
};

