#include "stdafx.h"
#include "..\Include\MidBoss_Laser_Charge.h"

#include "MidBoss_Define.h"

MidBoss_Laser_Charge::MidBoss_Laser_Charge()
{
}


MidBoss_Laser_Charge::~MidBoss_Laser_Charge()
{
}

void MidBoss_Laser_Charge::Initialize()
{
}

void MidBoss_Laser_Charge::EnterState()
{
	g_chargeDuration = GetFloat(_g_laserChargeDuration);
	
	m_timer = 0.f;
}

void MidBoss_Laser_Charge::UpdateState()
{
	// charge effect

	m_timer += dTime;

	if (m_timer >= g_chargeDuration)
	{
		SetState(_sn_laserFire);
		return;
	}
}

void MidBoss_Laser_Charge::ExitState()
{
}
