#include "Collision.h"

USING(Nalmak)

Collision::Collision(GameObject * _obj, const Vector3 & _hitPoint)
{

	assert(L"Object is nullptr!" && _obj);
	m_object = _obj;
	m_hitPoint = _hitPoint;
}
