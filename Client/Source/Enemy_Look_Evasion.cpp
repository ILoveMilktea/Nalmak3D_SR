#include "stdafx.h"
#include "..\Include\Enemy_Look_Evasion.h"
#include "Enemy_Bullet_Manager.h"
#include "EnemyManager.h"


Look_Evasion::Look_Evasion()
{
}


Look_Evasion::~Look_Evasion()
{
}

void Look_Evasion::Initialize()
{
	m_pPlayer = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);

	if (m_pPlayer == nullptr)
	{
		assert(L"플레이어 못받은거 같은데여 ㅋㅋ;;" && 0);
	}
}

void Look_Evasion::EnterState()
{

}

void Look_Evasion::UpdateState()
{
	m_fLookDelta += dTime;
	m_fFpmDelta += dTime;

	//if (m_fLookDelta >= 1.f)
	//{
		m_transform->LookAt(m_pPlayer, 1.f);
		//m_fLookDelta = 0.f;
	//}
	
	if (m_fFpmDelta >= 60.f / m_fFpm)
	{
		m_fBurstDelta += dTime;

		if (m_fBurstDelta >= 0.1f)
		{
			Bullet_Manager::GetInstance()->Gun_Evasion(m_transform->position, m_transform->rotation);
			++m_iCount;
			m_fBurstDelta = 0.f;
		}

		if (m_iCount >= 3)
		{
			m_fFpmDelta = 0.f;
			m_iCount = 0;
		}
	}

	Exit();

}

void Look_Evasion::ExitState()
{
	
}

