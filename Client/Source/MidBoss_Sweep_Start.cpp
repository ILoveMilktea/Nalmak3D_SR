#include "stdafx.h"
#include "..\Include\MidBoss_Sweep_Start.h"
#include "MidBoss_Define.h"

MidBoss_Sweep_Start::MidBoss_Sweep_Start()
{
}


MidBoss_Sweep_Start::~MidBoss_Sweep_Start()
{
}

void MidBoss_Sweep_Start::Initialize()
{
	SetFloat(_g_sweepDuration, 10.f);
	SetFloat(_g_sweepMoveRange, 50.f);
	SetFloat(_g_sweepFireTerm, 0.1f);
	SetInteger(_g_sweepBranchCount, 3);
}

void MidBoss_Sweep_Start::EnterState()
{
	SetFloat(_g_sweepPatternTimer, 0.f);
	SetFloat(_g_sweepFireTimer, 0.f);
}

void MidBoss_Sweep_Start::UpdateState()
{
	SetState(_sn_sweepMoveToForward);
}

void MidBoss_Sweep_Start::ExitState()
{
}
