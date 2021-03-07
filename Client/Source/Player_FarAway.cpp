#include "stdafx.h"
#include "..\Include\Player_FarAway.h"


Player_FarAway::Player_FarAway()
{
}


Player_FarAway::~Player_FarAway()
{
}

void Player_FarAway::Initialize()
{

}

void Player_FarAway::EnterState()
{

}

void Player_FarAway::UpdateState()
{
	m_fSpd = dTime * 500.f;

	Vector3 vforward = m_transform->GetForward();
	D3DXVec3Normalize(&vforward, &vforward);

	m_transform->position += vforward * m_fSpd;
}

void Player_FarAway::ExitState()
{

}
