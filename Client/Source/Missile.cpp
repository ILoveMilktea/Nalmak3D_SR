#include "stdafx.h"
#include "..\Include\Missile.h"



// Missile's Initial rotate valvue must be given like bullet.

Missile::Missile(Desc * _desc)
{
	m_fMaxSpd = _desc->fMaxSpd;
	m_vDest = _desc->vDest;
}

Missile::~Missile()
{

}

void Missile::Initialize()
{
}

void Missile::Update()
{
	Accelerate(m_fMaxSpd);

	Go_Destination();

	DEBUG_LOG(L"미사일 쓔웅", m_vDest);
	DEBUG_LOG(L"미사일 현재 위치", m_transform->position);
}

void Missile::Accelerate(float _maxSpd)
{
	if (m_fMaxSpd >= m_fCurSpd)
	{
		m_fCurSpd += dTime * 50.f;
	}
}

void Missile::Go_Destination()
{	

	Vector3 vDir = m_vDest - m_transform->position;
	D3DXVec3Normalize(&vDir, &vDir);
	
	Vector3 vDest;
	D3DXVec3Normalize(&vDest, &m_vDest);

	Quaternion qTemp;
	m_transform->LookAt(vDest, 10.f, &qTemp);
	m_transform->rotation = qTemp;

	m_transform->position += vDir * m_fCurSpd * dTime;
	//m_transform->position += m_transform->GetForward() * m_fCurSpd * dTime;
}

void Missile::Boom()
{
	if (m_transform->position == m_vDest)
	{
		DEBUG_LOG(L"펑", m_iA);
	}
	
	DESTROY(m_gameObject);
}
