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
		DESTROY((GameObject*)this);
	}
}
