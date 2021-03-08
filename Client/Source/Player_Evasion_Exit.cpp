#include "stdafx.h"
#include "..\Include\Player_Evasion_Exit.h"
#include "Player_Boss_Enter.h"


Player_Evasion_Exit::Player_Evasion_Exit()
{
}


Player_Evasion_Exit::~Player_Evasion_Exit()
{
}

void Player_Evasion_Exit::Initialize()
{
}

void Player_Evasion_Exit::EnterState()
{
	CalcDir();
}

void Player_Evasion_Exit::UpdateState()
{
	//To Vector3(0,0,0)
	
	CalcDir();
	m_transform->position += m_vDir * dTime;
	RotReset();

	if (m_fSpd <= 0.1f && !m_bNext)
	{
		m_gameObject->GetComponent<StateControl>()->SetState(L"playerBoss_Enter");
		m_bNext = true;
	}

	//DEBUG_LOG(L"Rotz", m_transform->rotation.z);
	//DEBUG_LOG(L"Exit Spd", m_fSpd);
}

void Player_Evasion_Exit::ExitState()
{
}

void Player_Evasion_Exit::CalcDir()
{
	m_vDir = Vector3(0.f, 0.f, 0.1f) - m_transform->position;
	m_fSpd = D3DXVec3Length(&m_vDir);
}

void Player_Evasion_Exit::RotReset()
{
	if (m_transform->rotation.z < 0.f) //오른쪽으로 가 있음. 왼쪽으로 기울어있다는 소리.
	{
		Quaternion qZAxis = m_transform->RotateAxis(m_transform->GetForward(), m_fSpd*  dTime * 1.f);
		m_transform->rotation *= qZAxis;
	}

	if (m_transform->rotation.z > 0.f)
	{
		Quaternion qZAxis = m_transform->RotateAxis(m_transform->GetForward(), m_fSpd* dTime * -1.f);
		m_transform->rotation *= qZAxis;
	}


}
