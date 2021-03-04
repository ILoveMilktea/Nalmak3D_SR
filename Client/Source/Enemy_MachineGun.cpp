#include "stdafx.h"
#include "..\Include\Enemy_MachineGun.h"



MachineGun::MachineGun(Desc* _desc)
{
	m_fSpd = _desc->fSpd;
	m_iDamage = _desc->iDmg;

	m_bStraight = _desc->bStraight;
	m_vDest = _desc->vDest;


}


MachineGun::~MachineGun()
{
}

void MachineGun::Initialize()
{

}

void MachineGun::Update()
{
	CalcDir();

	m_fDeltaTime += dTime;

	if (m_bStraight)
	{
		Straight_Shoot();
	}
	else 
	{
		Dest_Shoot();
	}
	
	if (m_fDeltaTime >= 10.f) 
	{
		DESTROY(m_gameObject);
	}

}

void MachineGun::OnTriggerEnter(Collisions & _collision)
{
	//MainGame에서 충돌 확인할 Layer설정 해줘야함.
	//아님 안함
	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_PLAYER)
		{
			DESTROY(m_gameObject);
		}
	}
}

void MachineGun::OnTriggerStay(Collisions & _collision)
{
}

void MachineGun::OnTriggerExit(Collisions & _collision)
{
}

void MachineGun::Go_Straight()
{
	m_transform->position += m_transform->GetForward() * m_fSpd * dTime;
}

void MachineGun::Straight_Shoot()
{
	Go_Straight();
}

void MachineGun::CalcDir()
{
	if (m_bFirst == true && m_bStraight == false)
	{
		m_vDir = m_vDest - m_transform->position;
		D3DXVec3Normalize(&m_vDir, &m_vDir);

		m_bFirst = false;
	}
}

void MachineGun::Dest_Shoot()
{
	m_transform->position += m_vDir * m_fSpd * dTime;
}
