#pragma once
#include "Component.h"
class Bullet_GoStraight :
	public Component
{
public:
	struct Desc
	{
		float speed = 0.f;
	};
public:
	Bullet_GoStraight(Desc* _desc);
	~Bullet_GoStraight();
public:
	void Fly();
	void Explosion();
private:
	Vector3 m_dir;
	float m_speed;
	ParticleRenderer* m_particle;

};

