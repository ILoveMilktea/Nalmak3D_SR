#include "stdafx.h"
#include "..\Include\Enemy_AirFire_TargetPlane.h"


Enemy_AirFire_TargetPlane::Enemy_AirFire_TargetPlane(Desc * _desc)
{
	
}

Enemy_AirFire_TargetPlane::~Enemy_AirFire_TargetPlane()
{
}

void Enemy_AirFire_TargetPlane::Initialize()
{
}

void Enemy_AirFire_TargetPlane::Update()
{
	m_fDelta += dTime;

	if (m_fDelta >= 2.f)
	{
		DESTROY(m_gameObject);
	}

}
