#include "stdafx.h"
#include "..\Include\MidBoss_Wave_Start.h"

#include "MidBoss_Define.h"


MidBoss_Wave_Start::MidBoss_Wave_Start()
{
}


MidBoss_Wave_Start::~MidBoss_Wave_Start()
{
}

void MidBoss_Wave_Start::Initialize()
{
}

void MidBoss_Wave_Start::EnterState()
{
	SetInteger(_g_waveIndex, 0);
	SetInteger(_g_waveCount, 3);

	SetFloat(_g_waveAngle, 100.f);
	SetFloat(_g_waveTerm, 0.3f);
	SetInteger(_g_waveBulletCount, 10);
	SetInteger(_g_waveAttackCount, 3);
	SetFloat(_g_waveIdleDuration, 1.f);
}

void MidBoss_Wave_Start::UpdateState()
{
	SetState(_sn_waveIdle);
}

void MidBoss_Wave_Start::ExitState()
{
}
