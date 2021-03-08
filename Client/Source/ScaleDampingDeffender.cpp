#include "stdafx.h"
#include "ScaleDampingDeffender.h"




ScaleDampingDeffender::ScaleDampingDeffender(Desc * _desc)
{
	m_dampingSpeed = _desc->dampingSpeed;
	m_maximumScale = _desc->maximumScale ;
	m_axis = _desc->axisDir;
	m_retainTime = _desc->m_retainTime;
}

ScaleDampingDeffender::~ScaleDampingDeffender()
{
}

void ScaleDampingDeffender::Initialize()
{
	// 
	m_spherCollider = m_gameObject->GetComponent<SphereCollider>();
	m_material = GetComponent<VIBufferRenderer>()->GetMaterial();

	assert(L"NULL" && m_spherCollider);

}

void ScaleDampingDeffender::Update()
{


	if (m_retainTime > 0 && m_maximumScale >= m_transform->scale.x
		&& m_maximumScale >= m_transform->scale.y
		&& m_maximumScale >= m_transform->scale.z ) // 커지기
	{
		 m_transform->scale.x += dTime * m_dampingSpeed;
		m_transform->scale.y += dTime * m_dampingSpeed;
		m_transform->scale.z += dTime * m_dampingSpeed;

		//m_material->SetFloat("g_strength",  0.1f);
	}
	else
	{
		m_retainTime -= dTime;
	}
		

	if (m_retainTime <= 0.f) // 작아지기
	{
		m_transform->scale.x -= dTime * m_dampingSpeed;
		m_transform->scale.y -= dTime * m_dampingSpeed;
		m_transform->scale.z -= dTime * m_dampingSpeed;
	}
	else if (m_retainTime > 0.f)
	{
		AxisRotate(m_axis);
	}

	if (0 >= m_transform->scale.x
		|| 0 >= m_transform->scale.y
		|| 0 >= m_transform->scale.z)
	{
		m_gameObject->GetTransform()->DeleteParent();
		DESTROY(m_gameObject);
		m_gameObject = nullptr;
	}
}

void ScaleDampingDeffender::LateUpdate()
{
	m_spherCollider->SetRadius(m_transform->scale.x * 0.5f);
}

void ScaleDampingDeffender::AxisRotate(Vector3 _axis)
{
	Quaternion quaterRotY;
	D3DXQuaternionRotationAxis(&quaterRotY, &_axis,  dTime );
	m_transform->rotation *= quaterRotY;
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