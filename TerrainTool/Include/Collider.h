#pragma once
#include "Component.h"
class NALMAK_DLL Collider abstract :
	public Component
{
	friend class CollisionManager;
protected:
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void PreRender() override;
	virtual void Release() override;
protected:
	Vector3 m_center;
	_COLLISION_LAYER m_collisionLayer;
	COLLIDER_TYPE m_type;
	GameObject* m_colliderDebug;

public:
	void SetCollisionLayer(_COLLISION_LAYER _layer) { m_collisionLayer = _layer; }
	const Vector3& GetCenter() { return m_center; }
	COLLIDER_TYPE GetType() { return m_type; }
private:
	class CollisionManager* m_collisionManager;
	

};

