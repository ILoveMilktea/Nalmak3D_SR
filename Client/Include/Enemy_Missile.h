#pragma once

#include "Component.h"

class Missile :
	public Component
{ 
public:
	struct Desc
	{
		float	fMaxSpd = 100.f;
		int		iMinDmg = 10;
		int		iMaxDmg = 50;
	};

public:
	Missile(Desc* _desc);
	virtual ~Missile();

public:
	virtual void Initialize() override;
	virtual void Update() override;

	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;

public:
	void Accelerate(float _maxSpd);

	void Boom();

private:
	int	m_iMinDmg = 0;
	int m_iMaxDmg = 0;

	float m_fCurSpd = 0.f;
	float m_fMaxSpd = 0.f;

	float m_fMissileDelta = 0.f;

	bool	m_bEffect = false;
};

