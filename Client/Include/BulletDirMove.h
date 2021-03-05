#pragma once
#include "Component.h"
class BulletDirMove :
	public Component
{
public:
	struct Desc
	{
		float speed = 0.f;
	};
public:
	BulletDirMove(Desc* _desc);
	virtual ~BulletDirMove();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;
private:
	Vector3 m_dir;
	float m_speed;
};

