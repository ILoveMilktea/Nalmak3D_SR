#include "stdafx.h"
#include "..\Include\MidBoss_Idle.h"

#include "InputManager.h"
#include "MidBoss_Define.h"
#include "Enemy_MidBoss.h"

MidBoss_Idle::MidBoss_Idle()
{
}


MidBoss_Idle::~MidBoss_Idle()
{
}

void MidBoss_Idle::Initialize()
{
	SetInteger(_g_patternIndex, 0);
}

void MidBoss_Idle::EnterState()
{
	g_patternIndex = GetInteger(_g_patternIndex);
	if (g_patternIndex > 4)
		g_patternIndex = 0;

	m_stateTimer = 0.f;
	m_stateTerm = 3.f;
}

void MidBoss_Idle::UpdateState()
{
	Enemy_MidBoss::MODE mode = m_stateControl->GetComponent<Enemy_MidBoss>()->m_mode;

	switch (mode)
	{
	case Enemy_MidBoss::AUTO:
		m_stateTimer += dTime;
		if (m_stateTimer > m_stateTerm)
		{
			switch ((PATTERN)g_patternIndex)
			{
			case WAVE:
				SetState(_sn_waveStart);
				return;
			case SWEEP:
				SetState(_sn_sweepStart);
				return;
			case HOMING:
				SetState(_sn_laserStart);
				return;
			case DEFENSE:
				SetState(_sn_defenseStart);
				return;
			default:
				g_patternIndex = 0;
				break;
			}
		}
		break;
	case Enemy_MidBoss::CONTROL:
		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F1))
		{
			SetState(_sn_waveStart);
			return;
		}
		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F2))
		{
			SetState(_sn_sweepStart);
			return;
		}
		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F3))
		{
			SetState(_sn_laserStart);
			return;
		}
		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F4))
		{
			SetState(_sn_defenseStart);
			return;
		}
		break;
	}
}

void MidBoss_Idle::ExitState()
{
	++g_patternIndex;
	SetInteger(_g_patternIndex, g_patternIndex);
}
