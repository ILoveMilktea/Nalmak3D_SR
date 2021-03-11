#include "stdafx.h"
#include "..\Include\MidBoss_Laser_Discharge.h"

#include "MidBoss_Define.h"

MidBoss_Laser_Discharge::MidBoss_Laser_Discharge()
{
}


MidBoss_Laser_Discharge::~MidBoss_Laser_Discharge()
{
}

void MidBoss_Laser_Discharge::Initialize()
{
}

void MidBoss_Laser_Discharge::EnterState()
{
	g_dischargeDuration = GetFloat(_g_laserDischargeDuration);

	m_timer = 0.f;
}

void MidBoss_Laser_Discharge::UpdateState()
{
	// discharge effect

	m_timer += dTime;

	if (m_timer >= g_dischargeDuration)
	{
		SetState(_sn_laserAttach);
		return;
	}

#ifdef _DEBUG
	if (InputManager::GetInstance()->GetKeyDown(_NEXT_STATE_KEY))
	{
		SetState(_sn_laserAttach);
		return;
	}
#endif // _DEBUG
}

void MidBoss_Laser_Discharge::ExitState()
{
}
