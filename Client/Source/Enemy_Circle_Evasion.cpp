#include "stdafx.h"
#include "..\Include\Enemy_Circle_Evasion.h"
#include "Enemy_Bullet_Manager.h"


Circle_Evasion::Circle_Evasion()
{
}


Circle_Evasion::~Circle_Evasion()
{
}

void Circle_Evasion::Initialize()
{
}

void Circle_Evasion::EnterState()
{
	
}

void Circle_Evasion::UpdateState()
{
	m_fStateDelta += dTime;
	m_fShootDelta += dTime;
	
	if (m_fShootDelta >= 1.5f)
	{

		m_qOrigin = m_transform->rotation;
		D3DXQuaternionIdentity(&m_qOrigin);
		D3DXQuaternionRotationAxis(&m_qOrigin, &Vector3(0.f, 1.f, 0.f), Deg2Rad * (45.f * m_iCount + m_fAngle)); // radian
	
		Bullet_Manager::GetInstance()->Gun_Evasion(m_transform->position, m_qOrigin);

		++m_iCount;

		if (m_iCount >= 8)
		{
			m_iCount = 0;
			m_fAngle += 10.f;
			m_fShootDelta = 0.f;

		}
	}

	Exit();

}

void Circle_Evasion::ExitState()
{
}
