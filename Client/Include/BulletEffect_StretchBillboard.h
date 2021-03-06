#pragma once
#include "Component.h"
class BulletEffect_StretchBillboard :
	public Component
{
public:
	struct Desc
	{
		float lifeTime;
		float speed;
		float stretchRatio;
		Vector3 direction;
	};
public:
	BulletEffect_StretchBillboard(Desc* _desc);
	~BulletEffect_StretchBillboard();
private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;
private:
	float m_lifeTime;
	float m_speed;
	float m_stretchRatio;
	Vector3 m_dir;
	Camera* m_camera;
	Material* m_material;
};

