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
	void Fire(Vector3 _pos, Quaternion _rot);

	

};

