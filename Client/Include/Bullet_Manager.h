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
	void Fire_Gun(Vector3 _start, Quaternion _rot, int _dmg = 10.f, float _spd = 50.f);
	void Fire_Missile(Vector3 _start, Quaternion _rot,
		int _minDmg = 0.f, int _maxDmg = 10.f,
		float _maxSpd = 150.f); //직선 미사일
	void Fire_Homing(); //유도 미사일

	/* for Evasion */
	void Gun_Evasion(Vector3 _start, Quaternion _rot);
	void Missile_Evasion(Vector2 _start);
	void Homing_Evasion(Vector2 _start, Vector2 _target);
	
	void Fire_Dest(Vector3 _start, Vector3 _dest, float _spd = 150.f);

public: /* for Player */
	void Fire_Player(Vector3 _start, Quaternion _rot, float _spd);
	

private:



};

