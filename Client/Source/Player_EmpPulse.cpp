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
	m_empMaterial = GetComponent<VIBufferRenderer>()->GetMaterial();
	m_cam = Core::GetInstance()->GetMainCamera()->GetTransform();
	m_empMaterial->SetFloat("g_distortionThickness", 0.05f);
}

void Player_EmpPulse::Update()
{
	Vector3 currentPos = m_transform->GetWorldPosition();
	Vector2 screenPos = m_cam->GetComponent<Camera>()->WorldToScreenPos(currentPos);
	screenPos += Vector2(HALF_WINCX, -HALF_WINCY);
	screenPos.y *= -1;
	m_empMaterial->SetVector("g_distortionCenter", Vector2(screenPos.x / WINCX, screenPos.y / WINCY));


	m_distanceToCam = Nalmak_Math::Distance(currentPos, m_cam->GetWorldPosition());


	if (!m_bShrink)
	{
		Bloat();
	}
	else { Shrink(); }

	Destroy();
	//m_gameObject->SetScale(Vector3(m_fCurRadius, m_fCurRadius, m_fCurRadius));
	m_gameObject->GetComponent<SphereCollider>()->SetRadius(m_fCurRadius);
}

void Player_EmpPulse::OnTriggerEnter(Collisions & _collision)
{
	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_ENEMY)
		{
			int i = 0;
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
		m_fCurRadius += dTime * 100.f;
		m_empMaterial->SetFloat("g_distortionSize", m_fCurRadius / m_distanceToCam);
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
		m_fCurRadius -= dTime *100.f;
		m_empMaterial->SetFloat("g_distortionThickness",  0.05f * m_fCurRadius / m_fMaxRadius);
	}

}

void Player_EmpPulse::Destroy()
{
	if (m_fCurRadius <= 0.f)
	{
		DESTROY(m_gameObject);
	}
}
