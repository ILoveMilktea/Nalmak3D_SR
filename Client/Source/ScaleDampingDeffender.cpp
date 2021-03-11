#include "stdafx.h"
#include "ScaleDampingDeffender.h"




ScaleDampingDeffender::ScaleDampingDeffender(Desc * _desc)
{
}

ScaleDampingDeffender::~ScaleDampingDeffender()
{
}

void ScaleDampingDeffender::Initialize()
{
	m_spherCollider = m_gameObject->GetComponent<SphereCollider>();
	m_material = GetComponent<VIBufferRenderer>()->GetMaterial();

	assert(L"NULL" && m_spherCollider);

	m_activeTimer = 0;
	m_currentScale = 0.f;
	m_targetScale = 3.f;
}

void ScaleDampingDeffender::Update()
{

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_5))
	{
		ActiveShield();
	}
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_6))
	{
		ShakeShield();
	}
	m_activeTimer += dTime;

	m_currentScale = Nalmak_Math::Lerp(m_currentScale, m_targetScale, dTime * 3);
	Vector3 scale = Vector3(1, 1, 1) * m_currentScale;

	m_transform->scale = scale;
	m_spherCollider->SetScale(scale);

	m_transform->RotateY(dTime);

	if (m_activeTimer > 5.f)
	{
		m_targetScale = 0.f;
	}
}

void ScaleDampingDeffender::LateUpdate()
{
	m_spherCollider->SetRadius(m_transform->scale.x * 0.5f);
}

void ScaleDampingDeffender::ActiveShield()
{
	m_targetScale = 3.f;
	m_activeTimer = 0.f;
}

void ScaleDampingDeffender::ShakeShield()
{
	m_currentScale = 3.3f;
}

void ScaleDampingDeffender::OnTriggerEnter(Collisions & _collision)
{
	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_BULLET_ENEMY)
		{
			DESTROY(obj.GetGameObject());
		}
	}

}

void ScaleDampingDeffender::OnTriggerStay(Collisions & _collision)
{
}

void ScaleDampingDeffender::OnTriggerExit(Collisions & _collision)
{
}