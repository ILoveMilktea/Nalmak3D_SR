#include "stdafx.h"
#include "..\Include\Missile.h"



// Missile's Initial rotate valvue must be given like bullet.

Missile::Missile(Desc * _desc)
{
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
	}

	if (m_fMissileDelta >= 0.5f)
	{//발사하고 가속도
		Accelerate(m_fMaxSpd);
		m_transform->position += m_transform->GetForward() * m_fCurSpd * dTime;
	}

	//m_transform->position = Nalmak_Math::Clamp(m_transform,)



	Boom();
	DEBUG_LOG(L"미사일 현재 위치", m_transform->position);
	DEBUG_LOG(L"미사일 속도", m_fCurSpd);
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

//void Missile::Go_Destination()
//{	
//
//	Vector3 vDir = m_vDest - m_transform->position;
//	D3DXVec3Normalize(&vDir, &vDir);
//	
//	Vector3 vDest;
//	D3DXVec3Normalize(&vDest, &m_vDest);
//
//	//Quaternion qTemp;
//	//m_transform->LookAt(vDest, 10.f, &qTemp);
//	//m_transform->rotation = qTemp;
//
//
//	m_transform->position += vDir * m_fCurSpd * dTime;
//	//m_transform->position += m_transform->GetForward() * m_fCurSpd * dTime;
//}

void Missile::Boom()
{
	if (m_fMissileDelta >= 10.f)
	{
		DEBUG_LOG(L"펑", m_iA);
		DESTROY(m_gameObject);
	}
	
}
