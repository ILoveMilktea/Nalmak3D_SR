#include "stdafx.h"
#include "..\Include\MidBoss_Wave_Idle.h"
#include "MidBoss_Define.h"


MidBoss_Wave_Idle::MidBoss_Wave_Idle()
{
}


MidBoss_Wave_Idle::~MidBoss_Wave_Idle()
{
}

void MidBoss_Wave_Idle::Initialize()
{
}

void MidBoss_Wave_Idle::EnterState()
{
	g_waveIdleDuration = GetFloat(_g_waveIdleDuration);

	m_idleTimer = 0.f;

	g_waveIndex = GetInteger(_g_waveIndex);
	g_waveCount = GetInteger(_g_waveCount);

	++g_waveIndex;

}

void MidBoss_Wave_Idle::UpdateState()
{
	m_idleTimer += dTime;

	if (m_idleTimer > g_waveIdleDuration)
	{
		if (g_waveIndex > g_waveCount)
			SetState(_sn_moveToCenter);
		else
			SetState(_sn_waveAttack);

	}
	

#ifdef _DEBUG
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F9))
	{
		SetState(_sn_idle);
		return;
	}
#endif // _DEBUG
}

void MidBoss_Wave_Idle::ExitState()
{
	SetInteger(_g_waveIndex, g_waveIndex);
}
