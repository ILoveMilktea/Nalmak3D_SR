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
	// state order setting
	m_stateOrder.emplace_back(_sn_moveLeft);
	m_stateOrder.emplace_back(_sn_moveToCenter);
	m_stateOrder.emplace_back(_sn_waveStart);
	m_stateOrder.emplace_back(_sn_rotateAccel);
	m_stateOrder.emplace_back(_sn_sweepStart);
	m_stateOrder.emplace_back(_sn_laserStart);
	m_stateOrder.emplace_back(_sn_moveRight);
	m_stateOrder.emplace_back(_sn_rotateAccel);
	m_stateOrder.emplace_back(_sn_waveStart);
	m_stateOrder.emplace_back(_sn_moveLeft);
	m_stateOrder.emplace_back(_sn_waveStart);
	m_stateOrder.emplace_back(_sn_rotateAccel);
	m_stateOrder.emplace_back(_sn_sweepStart);

	m_curOrder = m_stateOrder.begin();
}

void MidBoss_Idle::EnterState()
{
	if (m_curOrder == m_stateOrder.end())
		m_curOrder = m_stateOrder.begin();


	m_stateTimer = 0.f;
	m_stateDuration = 3.f;
}

void MidBoss_Idle::UpdateState()
{
	m_stateTimer += dTime;
	if (m_stateTimer > m_stateDuration)
	{
		SetState(*m_curOrder);
	}


#ifdef _DEBUG
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

	if (InputManager::GetInstance()->GetKeyDown(_NEXT_STATE_KEY))
	{
		SetState(*m_curOrder);
		return;
	}
#endif // _DEBUG
}

void MidBoss_Idle::ExitState()
{
	++m_curOrder;
}
