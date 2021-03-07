#include "stdafx.h"
#include "..\Include\Player_Evasion_Move.h"


Player_Evasion_Move::Player_Evasion_Move()
{
}


Player_Evasion_Move::~Player_Evasion_Move()
{
}

void Player_Evasion_Move::Initialize()
{
}

void Player_Evasion_Move::EnterState()
{

}

void Player_Evasion_Move::UpdateState()
{

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W)
		&& m_transform->position.z < 45.f)
	{
		m_transform->position.z += 20.f * dTime;

	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_S)
		&& m_transform->position.z > -45.f)
	{
		m_transform->position.z -= 20.f* dTime;
	}

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_D)
		&& m_transform->position.x < 85.f)
	{
		m_transform->position.x += 20.f* dTime;
		if (m_transform->rotation.z >= -0.4f)
		{
			Lean(RIGHT);
		}
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_A)
		&& m_transform->position.x > -85.f)
	{
		m_transform->position.x -= 20.f* dTime;
		if (m_transform->rotation.z <= 0.4f)
		{
			Lean(LEFT);
		}
	}
}

void Player_Evasion_Move::ExitState()
{

}

void Player_Evasion_Move::Lean(int _a)
{
	Vector3 EulerRotation = m_transform->GetEulerRotation();

	m_fRotZ = _a * dTime * 2.f;
	Quaternion qZAxis = m_transform->RotateAxis(m_transform->GetForward(), m_fRotZ);
	m_transform->rotation *= qZAxis;
}
