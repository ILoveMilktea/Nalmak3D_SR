#include "stdafx.h"
#include "..\Include\MidBoss_MoveToCenter.h"
#include "MidBoss_Define.h"

MidBoss_MoveToCenter::MidBoss_MoveToCenter()
{
}


MidBoss_MoveToCenter::~MidBoss_MoveToCenter()
{
}

void MidBoss_MoveToCenter::Initialize()
{
}

void MidBoss_MoveToCenter::EnterState()
{
	m_startPosition = m_transform->position;
	m_centerPosition = _MIDBOSS_CENTERPOS;	

	m_lerpTimer = 0.f;
	m_lerpDuration = 1.f;
}

void MidBoss_MoveToCenter::UpdateState()
{
	float inverseRate = 1.f - m_lerpTimer / m_lerpDuration;
	float sLerpTimer = 1.f - inverseRate * inverseRate;
	m_transform->position =  Nalmak_Math::Lerp(m_startPosition, m_centerPosition, sLerpTimer);

	m_lerpTimer += dTime;

	if (m_lerpTimer >= m_lerpDuration)
	{
		m_transform->position = m_centerPosition;
		SetState(_sn_idle);
		return;
	}
}

void MidBoss_MoveToCenter::ExitState()
{
}
