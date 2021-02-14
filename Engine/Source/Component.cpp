#include "..\Include\Component.h"

USING(Nalmak)
#include "Transform.h"
Component::Component()
{
	m_active = true;
	m_dead = false;
	m_name = "default";
}


Component::~Component()
{
}

void Component::OnEnable()
{
}

void Component::OnDisable()
{
}

void Component::Initialize()
{
}

void Component::Update()
{
}

void Component::LateUpdate()
{
}

void Component::Release()
{
}

void Component::PreRender()
{
}

void Component::PostRender()
{
}

void Component::OnTriggerEnter(Collisions & _collision)
{
}

void Component::OnTriggerStay(Collisions & _collision)
{
}

void Component::OnTriggerExit(Collisions & _collision)
{
}

void Component::SetActive(bool _active)
{
	m_active = _active;
	if (m_active)
		OnEnable();
	else
		OnDisable();

}

bool Component::GetActive()
{
	return m_active;
}

void Component::SetPosition(const Vector3 & _pos)
{
	m_transform->position = _pos;
}

void Component::SetScale(const Vector3 & _scale)
{
	m_transform->scale = _scale;
}
