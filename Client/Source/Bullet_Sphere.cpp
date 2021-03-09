#include "stdafx.h"
#include "..\Include\Bullet_Sphere.h"

#include "PlayerInfoManager.h"
#include "ItemManager.h"


Bullet_Sphere::Bullet_Sphere(Desc * _desc)
{
	m_lifeTime = _desc->lifeTime;
	m_speed = _desc->speed;
	m_stretchRatio = _desc->stretchRatio;
	m_dir = _desc->direction;

	m_dmg = _desc->dmg;
}

Bullet_Sphere::~Bullet_Sphere()
{
}

void Bullet_Sphere::Initialize()
{
	m_camera = Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA)->GetComponent<Camera>();


	m_material = GetComponent<VIBufferRenderer>()->GetMaterial();
}

void Bullet_Sphere::Update()
{
	if (m_lifeTime < 0)
	{
		DESTROY(m_gameObject);
		return;
	}
	m_lifeTime -= dTime;


	float angle = Nalmak_Math::Dot(Vector3(0, 1, 0), m_dir);

	Vector3 axis;
	D3DXVec3Cross(&axis, &Vector3(0, 1, 0), &m_dir);
	D3DXQuaternionRotationAxis(&m_transform->rotation, &axis, acos(angle));
	//m_transform->SetRotation(90,0,0);

	m_transform->position += m_dir * m_speed * dTime;

}

void Bullet_Sphere::OnTriggerEnter(Collisions & _collision)
{
	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_PLAYER)
		{
			PlayerInfoManager::GetInstance()->SetDamage((int)m_dmg);

			DESTROY(m_gameObject);
		}
	}
}

void Bullet_Sphere::OnTriggerStay(Collisions & _collision)
{
}

void Bullet_Sphere::OnTriggerExit(Collisions & _collision)
{
}
