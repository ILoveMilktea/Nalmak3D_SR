#include "stdafx.h"
#include "..\Include\Player_Evasion_Enter.h"


Player_Evasion_Enter::Player_Evasion_Enter()
{
}


Player_Evasion_Enter::~Player_Evasion_Enter()
{
}

void Player_Evasion_Enter::Initialize()
{
}

void Player_Evasion_Enter::EnterState()
{
	m_transform->SetPosition(Vector3(0.f, 0.f, -100.f));
	m_transform->SetRotation(0.f, 0.f, 0.f);
	m_fSpd = 0.f - m_transform->position.z;

}

void Player_Evasion_Enter::UpdateState()
{
	if (m_fSpd >= 0.2f)
	{
		Decelerate();
		m_transform->position.z += m_fSpd * dTime;
	}
	else 
	{
		m_gameObject->GetComponent<StateControl>()->SetState(L"playerEvasion_Move");
	}


	//DEBUG_LOG(L"Player Spd", m_fSpd);
}

void Player_Evasion_Enter::ExitState()
{
}

void Player_Evasion_Enter::Decelerate()
{
	m_fSpd = 0.f - m_transform->position.z;
	m_fSpd = std::fabs(m_fSpd);
}
