#include "stdafx.h"
#include "ScaleDampingDeffender.h"




ScaleDampingDeffender::ScaleDampingDeffender(Desc * _desc)
{
	m_dampingSpeed = _desc->dampingSpeed;
	m_maximumScale = _desc->maximumScale;
	m_axis = _desc->axisDir;
	m_retainTime = _desc->m_retainTime;
}

ScaleDampingDeffender::~ScaleDampingDeffender()
{
}

void ScaleDampingDeffender::Initialize()
{
	// 

}

void ScaleDampingDeffender::Update()
{
	if (m_retainTime > 0 && m_maximumScale >= m_transform->scale.x
		&& m_maximumScale >= m_transform->scale.y
		&& m_maximumScale >= m_transform->scale.z )
	{
		 m_transform->scale.x += dTime * m_dampingSpeed;
		m_transform->scale.y += dTime * m_dampingSpeed;
		m_transform->scale.z += dTime * m_dampingSpeed;
	}
	else
	{
		m_retainTime -= dTime;
	}
		

	if (m_retainTime <= 0.f)
	{
		m_transform->scale.x -= dTime * m_dampingSpeed * 3.f;
		m_transform->scale.y -= dTime * m_dampingSpeed * 3.f;
		m_transform->scale.z -= dTime * m_dampingSpeed * 3.f;
		
	}
	else if (m_retainTime > 0.f)
	{
		AxisRotate();
	 
	}

	if (0 >= m_transform->scale.x
		|| 0 >= m_transform->scale.y
		|| 0 >= m_transform->scale.z)
	{
		DESTROY(m_gameObject);
	}
}

void ScaleDampingDeffender::AxisRotate()
{
	Quaternion quaterRotY;
	D3DXQuaternionRotationAxis(&quaterRotY, &Vector3(0.f,1.f,0.f),  dTime );
	m_transform->rotation *= quaterRotY;
}

