#pragma once
#include "Component.h"
class MidBoss_SingleBullet :
	public Component
{
public:
	struct Desc
	{
		float lifeTime;
		float speed;
		float stretchRatio;
		Vector3 direction;

		float dmg = 10.f;
	};

public:
	MidBoss_SingleBullet(Desc* _desc);
	~MidBoss_SingleBullet();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;

private:
	float m_dmg;
	float m_lifeTime;
	float m_speed;
	float m_stretchRatio;
	Vector3 m_dir;
	Camera* m_camera;
	Material* m_material;
};

