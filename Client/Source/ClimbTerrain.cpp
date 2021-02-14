#include "stdafx.h"
#include "..\Include\ClimbTerrain.h"


ClimbTerrain::ClimbTerrain(Desc * _desc)
{
	m_targetTerrain = _desc->terrain;
}

ClimbTerrain::~ClimbTerrain()
{
}

void ClimbTerrain::Initialize()
{
}

void ClimbTerrain::Update()
{
	
	//m_rigidbody->AddForce(m_planeInfo->GetDefaultForce());
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE::KEY_STATE_UP_ARROW))
	{
		m_transform->position += m_transform->GetForward() * 5 * dTime;

	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE::KEY_STATE_DOWN_ARROW))
	{
		m_transform->position -= m_transform->GetForward() * 5 * dTime;
	}


	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE::KEY_STATE_LEFT_ARROW))
	{
		m_transform->RotateY(-dTime * 60);
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE::KEY_STATE_RIGHT_ARROW))
	{
		m_transform->RotateY(dTime * 60);
	}


	float targetHeight = m_targetTerrain->GetHeight(m_transform->position);
	DEBUG_LOG(L"player", m_transform);
	m_transform->position.y = targetHeight;
}
