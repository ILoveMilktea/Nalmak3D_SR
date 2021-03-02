#include "stdafx.h"
#include "..\Include\PlayerTopViewMove.h"

#include "PlayerInfoManager.h"

#include "Bullet_Manager.h"


PlayerTopViewMove::PlayerTopViewMove()
{
}


PlayerTopViewMove::~PlayerTopViewMove()
{
}

void PlayerTopViewMove::Initialize()
{
}

void PlayerTopViewMove::EnterState()
{
	
}

void PlayerTopViewMove::UpdateState()
{
	
	TopViewMoving();


	Shooting();

	DEBUG_LOG(L"m_fRotz", m_fRotz);
	DEBUG_LOG(L"player Pos", m_transform->position);
}

void PlayerTopViewMove::ExitState()
{
}

void PlayerTopViewMove::TopViewMoving()
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
	


	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_MOUSE))
	{
		Bullet_Manager::GetInstance()->Fire_Player(m_transform->position, m_transform->rotation, 150.f);
	}



	
}

void PlayerTopViewMove::Shooting()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		Vector2 vCurPos = { m_transform->position.x,m_transform->position.z };
		Bullet_Manager::GetInstance()->Gun_Evasion(m_transform->position,m_transform->rotation);
	}

	if(InputManager::GetInstance()->GetKeyDown(KEY_STATE_RIGHT_MOUSE))
	{
		Vector2 vCurPos = { m_transform->position.x,m_transform->position.z };
		Bullet_Manager::GetInstance()->Missile_Evasion(vCurPos);
	}
}

void PlayerTopViewMove::Lean(int _a)
{
	
	Vector3 EulerRotation = m_transform->GetEulerRotation();
	
	m_fRotz = _a * dTime * 2.f;
	Quaternion qZAxis = m_transform->RotateAxis(m_transform->GetForward(), m_fRotz);
	m_transform->rotation *= qZAxis;
}
