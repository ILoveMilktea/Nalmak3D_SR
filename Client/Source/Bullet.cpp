#include "stdafx.h"
#include "..\Include\Bullet.h"



Bullet::Bullet(Desc* _desc)
{
	m_fSpd = _desc->fSpd;
	m_iDamage = _desc->iDmg;
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{

}

void Bullet::Update() 
{
	m_fDeltaTime += dTime;

	m_transform->position += m_transform->GetForward() * m_fSpd * dTime;
	
	if (m_fDeltaTime >= 10.f)
	{
		DESTROY(m_gameObject);
	}

}

void Bullet::OnTriggerEnter(Collisions & _collision)
{
	//MainGame���� �浹 Ȯ���� Layer���� �������.
	//�ƴ� ����
	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_ENEMY)
		{
			DEBUG_LOG(L"asdf", L"����ü���浹");
			DESTROY(m_gameObject);
		}
	}
}

void Bullet::OnTriggerStay(Collisions & _collision)
{
}

void Bullet::OnTriggerExit(Collisions & _collision)
{
}
