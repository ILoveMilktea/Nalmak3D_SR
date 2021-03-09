#include "stdafx.h"
#include "..\Include\MidBoss_Sweep_MoveToForward.h"

#include "MidBoss_Define.h"
#include "Enemy_MidBoss.h"
#include "PlayerInfoManager.h"

MidBoss_Sweep_MoveToForward::MidBoss_Sweep_MoveToForward()
{
}


MidBoss_Sweep_MoveToForward::~MidBoss_Sweep_MoveToForward()
{
}

void MidBoss_Sweep_MoveToForward::Initialize()
{
}

void MidBoss_Sweep_MoveToForward::EnterState()
{
	m_startPos = m_transform->position;

	m_playerPos = PlayerInfoManager::GetInstance()->GetPlayer()->GetTransform()->position;
	m_playerPos.z = _MIDBOSS_CENTERPOS.z;


	m_lerpTimer = 0.f;
	m_lerpDuration = 1.f;

}

void MidBoss_Sweep_MoveToForward::UpdateState()
{
	float inverseRate = 1.f - m_lerpTimer / m_lerpDuration;
	float sLerpTimer = 1.f - inverseRate*inverseRate;
	m_transform->position = Nalmak_Math::Lerp(m_startPos, m_playerPos, sLerpTimer);

	m_lerpTimer += dTime;

	if (m_lerpTimer >= m_lerpDuration)
	{
		m_transform->position = m_playerPos;
		SetState(_sn_sweepRight);
		return;
	}

#ifdef _DEBUG
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F9))
	{
		SetState(_sn_idle);
		return;
	}
#endif // _DEBUG
}

void MidBoss_Sweep_MoveToForward::ExitState()
{
	SetInteger(_g_sweepIsFirstMove, true);
	GetComponent<Enemy_MidBoss>()->SetRotateSpeed(_SPEED_HIGH);
}
