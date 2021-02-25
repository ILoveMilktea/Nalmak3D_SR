#pragma once
#include "Component.h"
class Bullet_Manager :
	public Component
{
public:
	struct Desc
	{


	};
public:
	Bullet_Manager(Desc* _desc);
	virtual ~Bullet_Manager();
	
private:
	static Bullet_Manager* m_Instance;
public:
	static Bullet_Manager* GetInstance();
	static void DeleteInstance();

public:
	virtual void Initialize() override;
	virtual void Update() override;

public: /* for Enemy */
	/* for DogFight */
	void Fire_Gun(Vector3 _start, Quaternion _rot, 
		float _fpm = 120.f, float _dmg = 10.f);
	void Fire_Missile(Vector3 _start, Quaternion _rot); //직선 미사일
	void Fire_Homing(); //유도 미사일

	/* for Evasion */
	void Gun_Evasion(Vector2 _start);
	void Missile_Evasion(Vector2 _start);
	void Homing_Evasion(Vector2 _start, Vector2 _target);


public:


private:
	float m_FireDelta = 0.f;
	float m_MissileDelta = 0.f;
	float m_HomingDelta = 0.f;


};

