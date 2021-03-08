#pragma once

#define _sn_appear				L"MidBoss_Appear"
#define _sn_idle				L"MidBoss_Idle"
#define _sn_move				L"MidBoss_Move"
#define _sn_moveToCenter		L"MidBoss_MoveToCenter"
#define _sn_rotate180			L"MidBoss_Rotate180"


#define _sn_waveStart			L"MidBoss_WaveStart"
#define _sn_waveIdle			L"MidBoss_WaveIdle"
#define _sn_waveAttack			L"MidBoss_WaveAttack"
	
#define _sn_laserStart			L"MidBoss_LaserStart"
#define _sn_laserSiege			L"MidBoss_LaserSiege"
#define _sn_laserDetach			L"MidBoss_LaserDetach"
#define _sn_laserCharge			L"MidBoss_LaserCharge"
#define _sn_laserFire			L"MidBoss_LaserFire"
#define _sn_laserDischarge		L"MidBoss_LaserDischarge"
#define _sn_laserAttach			L"MidBoss_LaserAttach"

#define _sn_defenseStart		L"MidBoss_DefenseStart"
#define _sn_defenseMove			L"MidBoss_DefenseMove"

#define _sn_sweepStart			L"MidBoss_SweepStart"
#define _sn_sweepLeft			L"MidBoss_SweepLeft"
#define _sn_sweepRight			L"MidBoss_SweepRight"
#define _sn_sweepMoveToForward	L"MidBoss_SweepMoveToForward"	

// --- state control global variable
#define _MIDBOSS_CENTERPOS	Vector3(0.f,0.f,50.f)
#define _MIDBOSS_CENTERROT	Quaternion(0.f,0.f,0.f,1.f)

#define _g_patternIndex			L"MidBoss_g_PatternIndex"
#define _g_centerPosition		L"MidBoss_g_CenterPosition"

#define _g_waveIndex			L"MidBoss_g_WaveIndex"
#define _g_waveCount			L"MidBoss_g_WaveCount"
#define _g_waveAngle			L"MidBoss_g_WaveAngle"
#define _g_waveTerm				L"MidBoss_g_WaveTerm"
#define _g_waveBulletCount		L"MidBoss_g_WaveBulletCount"
#define _g_waveAttackCount		L"MidBoss_g_WaveAttackCount"
#define _g_waveIdleDuration		L"MidBoss_g_WaveIdleDuration"

#define _g_sweepDuration		L"MidBoss_g_SweepDuration"
#define _g_sweepPatternTimer	L"MidBoss_g_SweepGlobalTimer"
#define _g_sweepMoveRange		L"MidBoss_g_SweepMoveRange"
#define _g_sweepFireTimer		L"MidBoss_g_SweepFireTimer"
#define _g_sweepFireTerm		L"MidBoss_g_SweepFireTerm"
#define _g_sweepBranchCount		L"MidBoss_g_SweepBranchCount"
#define _g_sweepIsFirstMove		L"MidBoss_g_SweepIsFirstMove"

#define _g_laserSiegeDuration		L"MidBoss_g_LaserSiegeDuration"
#define _g_laserDetachDuration		L"MidBoss_g_LaserDetachDuration"
#define _g_laserChargeDuration		L"MidBoss_g_LaserChargeDuration"
#define _g_laserFireDuration		L"MidBoss_g_LaserFireDuration"
#define _g_laserDischargeDuration	L"MidBoss_g_LaserDischargeDuration"
#define _g_laserAttachDuration		L"MidBoss_g_LaserAttachDuration"

#define _g_defenseIndex			L"MidBoss_g_DefenseIndex"