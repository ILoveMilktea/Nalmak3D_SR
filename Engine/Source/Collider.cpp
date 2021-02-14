#include "..\Include\Collider.h"
#include "CollisionManager.h"




void Collider::OnEnable()
{
	m_gameObject->ResetCollision();
}

void Collider::OnDisable()
{
	m_gameObject->ResetCollision();
}

void Collider::Initialize()
{
	m_collisionManager = CollisionManager::GetInstance();
}

void Collider::Update()
{
}

void Collider::LateUpdate()
{
	m_collisionManager->AddCollidier(this);
}

void Collider::PreRender()
{
}

void Collider::Release()
{
	m_collisionManager->DeleteCollider(this);
}
