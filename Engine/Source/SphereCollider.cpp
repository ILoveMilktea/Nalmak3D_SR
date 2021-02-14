#include "..\Include\SphereCollider.h"
#include "MeshRenderer.h"

SphereCollider::SphereCollider(Desc * _desc)
{
	m_center = _desc->offset;
	m_radius = _desc->radius;
	m_collisionLayer = _desc->collisionLayer;
	m_type = COLLIDER_TYPE_SPHERE;
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Initialize()
{
	Collider::Initialize();


	MeshRenderer::Desc render;
	render.mtrlName = L"debugCollider";
	render.meshName = L"sphere";
	m_colliderDebug = INSTANTIATE()->AddComponent<MeshRenderer>(&render);
	m_colliderDebug->SetParents(m_gameObject);
	m_colliderDebug->SetScale(m_radius * 2, m_radius * 2, m_radius * 2);
}


void SphereCollider::OnTriggerEnter(Collisions & _collision)
{
}

void SphereCollider::OnTriggerStay(Collisions & _collision)
{
	DEBUG_LOG(L"충돌!", L"충돌");
}

void SphereCollider::OnTriggerExit(Collisions & _collision)
{
}


void SphereCollider::Release()
{
	DESTROY(m_colliderDebug);
}
