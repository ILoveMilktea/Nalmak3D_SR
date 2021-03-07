#include "stdafx.h"
#include "..\Include\Camera_Boss.h"


Camera_Boss::Camera_Boss()
{
}


Camera_Boss::~Camera_Boss()
{
}

void Camera_Boss::Initialize()
{
}

void Camera_Boss::EnterState()
{
	Vector3 PlayerPos = PlayerInfoManager::GetInstance()->GetPlayer()->GetTransform()->position;
	m_transform->position.x = 0.f;
	m_transform->position.y = 0.f;
}

void Camera_Boss::UpdateState()
{
}

void Camera_Boss::ExitState()
{
}
