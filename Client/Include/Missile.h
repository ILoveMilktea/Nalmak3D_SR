#pragma once

#include "Component.h"

class Missile :
	public Component
{ 
public:
	struct Desc
	{
<<<<<<< HEAD
		float fMaxSpd = 200.f;
		int		iDmg = 50;
		Vector3 vDest = { 0,0,0 };
=======
		float fMaxSpd = 100.f;
		int		iDmg = 50.f;
>>>>>>> ac4e9fdfcccfe66fdf14e7a4ed8a3383c521456a
	};
public:
	Missile(Desc* _desc);
	virtual ~Missile();

public:
	virtual void Initialize() override;
	virtual void Update() override;

	void Go_Straight();
	void Accelerate(float _maxSpd);

	void Boom();
private:
	
	int	m_iDmg = 0;
	float m_fMaxSpd = 0.f;
	float m_fCurSpd = 1.f;
	
	float m_fMissileDelta = 0.f;

	int m_iA = 0;
};

