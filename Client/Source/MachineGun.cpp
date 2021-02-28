#include "stdafx.h"
#include "..\Include\MachineGun.h"



MachineGun::MachineGun(Desc* _desc)
{
	m_fSpd = _desc->fSpd;
	m_iDamage = _desc->iDmg;
}

MachineGun::~MachineGun()
{
}

void MachineGun::Initialize()
{

}

void MachineGun::Update()
{
	m_fDeltaTime += dTime;

	m_transform->position += m_transform->GetForward() * m_fSpd * dTime;
	
	if (m_fDeltaTime >= 10.f) 
	{
		DESTROY(m_gameObject);
	}

}

void MachineGun::OnTriggerEnter(Collisions & _collision)
{
	//MainGame���� �浹 Ȯ���� Layer���� �������.
	//�ƴ� ����
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
