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

public:
	void Fire(Vector3 _start, Quaternion _rot);
	void Fire_Missile(Vector3 _start, Quaternion _rot); //직선 미사일
	void Fire_Homing(); //유도 미사일

	void Fire_Evasion(Vector2 _start);
	void Missile_Evasion(Vector2 _start);
	void Homing_Evasion(Vector2 _start, Vector2 _target);

};

