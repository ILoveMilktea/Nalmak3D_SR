#pragma once
#include "Collider.h"
class NALMAK_DLL SphereCollider :
	public Collider
{
	friend class CollisionManager;
public:
	struct Desc
	{
		float radius = 0.5f;
		Vector3 offset = Vector3(0, 0, 0);
		_COLLISION_LAYER collisionLayer = 0;
	};
public:
	SphereCollider(Desc* _desc);
	~SphereCollider();
public:
	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
	void SetRadius(float _radius) { m_radius = _radius; }
	float GetRadius() { return m_radius; }
private:
	float m_radius;
};

