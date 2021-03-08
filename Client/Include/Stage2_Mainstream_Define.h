#pragma once

#define _sn_enter				L"State_Evasion_Enter"
#define _sn_airfire				L"State_Evasion_Airfire"
#define _sn_midboss				L"State_Evasion_Midboss"
#define _sn_midbossdead			L"State_Evasion_MidbossDead"

#define _sn_camera_wait			L"State_Camera_Wait"
#define _sn_camera_evasion		L"State_Camera_Evasion"

#define _sn_player_wait			L"State_Player_Wait"
#define _sn_player_evasion		L"State_Player_Evasion"

// --- state control global variable
#define _MIDBOSS_CENTERPOS	Vector3(0.f,0.f,30.f)
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