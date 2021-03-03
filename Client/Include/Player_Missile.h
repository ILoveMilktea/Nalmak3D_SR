#pragma once
#include "Component.h"
class Player_Missile :
	public Component
{
public:
	struct Desc
	{

	};
public:
	Player_Missile(Desc* _desc);
	~Player_Missile();


public:
	virtual void Create() = 0;
	virtual void Fly() = 0;
	virtual void Action() = 0;
	virtual void Bomb() = 0;

private:
	ParticleRenderer* m_particle;


};

