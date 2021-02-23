#pragma once

#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "Nalmak_Include.h"
class GameObject;
BEGIN(Nalmak)

class NALMAK_DLL Collision
{
	
	friend class CollisionManager;
public:
	Collision() = default;
private:
	Collision(GameObject* _obj, const Vector3& _hitPoint);
public:
	~Collision() = default;
public:
	GameObject* GetGameObject() { return m_object; }
	const Vector3& GetHitPoint() { return m_hitPoint; }
private:
	GameObject* m_object;
	Vector3 m_hitPoint;
};
END
#endif // !__COLLISION_H__
