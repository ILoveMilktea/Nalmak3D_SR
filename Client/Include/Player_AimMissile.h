#pragma once
#include "Player_Missile.h"
class Player_AimMissile :
	public Player_Missile
{
public:
	struct Desc
	{
		float speed = 30;
		Vector3 lastPlayerVelocity = { 0,0,0 };
	};
public:
	Player_AimMissile(Desc* _desc);
	~Player_AimMissile();
private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;
private:
	virtual void Create() override;
	virtual void Fly() override;
	virtual void Action() override;
	virtual void Bomb() override;
private:
	float m_speed;
	float m_fallingTimer;
	Vector3 m_dir;
	Vector3 m_lastPlayerVelocity;

private:
	ParticleRenderer* m_smokeParticle;
	ParticleRenderer* m_smokeLaunchParticle;

};

