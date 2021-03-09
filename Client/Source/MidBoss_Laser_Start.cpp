#include "stdafx.h"
#include "..\Include\MidBoss_Laser_Start.h"

#include "MidBoss_Define.h"
#include "Enemy_MidBoss.h"

MidBoss_Laser_Start::MidBoss_Laser_Start()
{
}


MidBoss_Laser_Start::~MidBoss_Laser_Start()
{
}

void MidBoss_Laser_Start::Initialize()
{
}

void MidBoss_Laser_Start::EnterState()
{
	SetFloat(_g_laserSiegeDuration, 1.f);
	SetFloat(_g_laserDetachDuration, 1.f);
	SetFloat(_g_laserChargeDuration, 2.f);
	SetFloat(_g_laserFireDuration, 3.f);
	SetFloat(_g_laserDischargeDuration, 2.f);
	SetFloat(_g_laserAttachDuration, 1.f);
}

void MidBoss_Laser_Start::UpdateState()
{
	SetState(_sn_laserSiege);
}

void MidBoss_Laser_Start::ExitState()
{
	GetComponent<Enemy_MidBoss>()->SetRotateSpeed(_SPEED_LOW);
}
