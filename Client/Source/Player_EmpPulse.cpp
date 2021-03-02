#include "stdafx.h"
#include "..\Include\Player_EmpPulse.h"


Player_EmpPulse::Player_EmpPulse(Desc * _desc)
{
	m_fMaxRadius = _desc->max_Radius;
}

Player_EmpPulse::~Player_EmpPulse()
{
}

void Player_EmpPulse::Initialize()
{
}

void Player_EmpPulse::Update()
{
	if (!m_bShrink)
	{
		Bloat();
	}
	else { Shrink(); }

	m_gameObject->SetScale(Vector3(m_fCurRadius, m_fCurRadius, m_fCurRadius));
	m_gameObject->GetComponent<SphereCollider>()->SetRadius(m_fCurRadius);
}

void Player_EmpPulse::OnTriggerEnter(Collisions & _collision)
{
	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_ENEMY)
		{
			
		}
	}
}

void Player_EmpPulse::OnTriggerStay(Collisions & _collision)
{
}

void Player_EmpPulse::OnTriggerExit(Collisions & _collision)
{
}

void Player_EmpPulse::Bloat()
{
	if (m_fCurRadius < m_fMaxRadius)
	{
		m_fCurRadius += dTime * 10.f;
	}
	else 
	{
		m_bShrink = true;
	}

}

void Player_EmpPulse::Shrink()
{
	if (m_fCurRadius > 0.f)
	{
		m_fCurRadius -= dTime *5.f;
	}

}

void Player_EmpPulse::Destroy()
{
	if (m_fCurRadius <= 0.f)
	{
		DESTROY(m_gameObject);
	}
}
