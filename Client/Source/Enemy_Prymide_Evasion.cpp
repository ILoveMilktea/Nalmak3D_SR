#include "stdafx.h"
#include "..\Include\Enemy_Prymide_Evasion.h"
#include "Enemy_Bullet_Manager.h"


Prymide_Evasion::Prymide_Evasion()
{
}


Prymide_Evasion::~Prymide_Evasion()
{
}

void Prymide_Evasion::Initialize()
{
}

void Prymide_Evasion::EnterState()
{
}

void Prymide_Evasion::UpdateState()
{
	//m_transform->position += m_transform->GetForward() *dTime;

	m_fShootDelta += dTime;

	if (m_fShootDelta >= 2.f)
	{
		m_fBurstDelta += dTime;

		if (m_fBurstDelta >= 0.2f)
		{
			for(int i = 0; i<5; ++i)
			{
				m_qOrigin = m_transform->rotation;
				D3DXQuaternionIdentity(&m_qOrigin);
				D3DXQuaternionRotationAxis(&m_qOrigin, &Vector3(0.f, 1.f, 0.f), D3DXToRadian(m_fAngle[i]+180.f));

				Bullet_Manager::GetInstance()->Gun_Evasion(m_transform->position, m_qOrigin);
			}

			m_fBurstDelta = 0.f;
			++m_iCount;
		}

		if (m_iCount >= 3)
		{
			m_fShootDelta = 0.f;
			m_iCount = 0;
		}

	}

	Exit();

}

void Prymide_Evasion::ExitState()
{
}
