#pragma once
#include "Component.h"
class Bullet :
	public Component
{
public:
	struct Desc
	{
		float	fSpd = 50.f;
		int		iDmg = 10;
	};
	
public:
	Bullet(Desc* _desc);
	virtual ~Bullet();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

private:
	
	float m_fSpd = 0.f;
	int m_iDamage = 0.f;

	float m_fDeltaTime = 0.f;
};

