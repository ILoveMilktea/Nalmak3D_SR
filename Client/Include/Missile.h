#pragma once

#include "Component.h"

class Missile :
	public Component
{ 
public:
	struct Desc
	{
		float fMaxSpd = 200.f;
		int		iDmg = 50;
		Vector3 vDest = { 0,0,0 };
	};
public:
	Missile(Desc* _desc);
	virtual ~Missile();

public:
	virtual void Initialize() override;
	virtual void Update() override;

	void Accelerate(float _maxSpd);

	void Go_Destination();

	void Boom();
private:
	Vector3 m_vDest = { 0.f, 0.f, 0.f };
	
	int	m_iDmg = 0;
	float m_fMaxSpd = 0.f;
	float m_fCurSpd = 1.f;
	
	int m_iA = 0;
};

