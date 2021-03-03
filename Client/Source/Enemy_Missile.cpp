#include "stdafx.h"
#include "..\Include\Enemy_Missile.h"



// Missile's Initial rotate valvue must be given like bullet.

Missile::Missile(Desc * _desc)
{
	m_iMinDmg = _desc->iMinDmg;
	m_iMaxDmg = _desc->iMaxDmg;

	m_fMaxSpd = _desc->fMaxSpd;
}

Missile::~Missile()
{

}

void Missile::Initialize()
{
	
	
}

void Missile::Update()
{
	m_fMissileDelta += dTime;

	if (m_fMissileDelta < 0.5f)
	{
		//약간 밑으로 내려간 다음에
		m_transform->position.y -= dTime * 5.f;
		if (m_bEffect == false)
		{
			m_bEffect = true;
		}
	}

	if (m_fMissileDelta >= 0.5f)
	{//발사하고 가속도
		if (m_bEffect)
		{/*Effect Setting Here*/
			
			m_bEffect = false;
		}
		Accelerate(m_fMaxSpd);
		m_transform->position += m_transform->GetForward() * m_fCurSpd * dTime;
	}

	Boom();
	DEBUG_LOG(L"미사일 현재 위치", m_transform->position);
	DEBUG_LOG(L"미사일 속도", m_fCurSpd);
}

void Missile::OnTriggerEnter(Collisions & _collision)
{
	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_PLAYER)
		{
			DESTROY(m_gameObject);
		}
	}
}

void Missile::OnTriggerStay(Collisions & _collision)
{
}

void Missile::OnTriggerExit(Collisions & _collision)
{
}

void Missile::Accelerate(float _maxSpd)
{
	if (m_fMaxSpd >= m_fCurSpd)
	{
		//m_fCurSpd += dTime * 50.f;
		m_fCurSpd = Nalmak_Math::Lerp(m_fCurSpd, m_fMaxSpd, dTime);
		//Lerp : 첫번째 인자의 수를 받아와서 MaxSpd의 비율에서 DTime만큼 증가함
		//		=> 그냥 += dTime 으로 하면 속도가 확 증가, 확 감소 하는디
		//			Lerp로 하면 시작지점과 끝지점을 매번 받아와서 그 안에서 비율로 증감하는거라서 등속도가 됨.

	}
}


void Missile::Boom()
{
	if (m_fMissileDelta >= 10.f)
	{
		DESTROY(m_gameObject);
	}
	
}
