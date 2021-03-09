#include "stdafx.h"
#include "..\Include\MidBoss_Laser_Attach.h"

#include "MidBoss_Define.h"
#include "Enemy_MidBoss.h"
#include "Enemy_BulletProof.h"

MidBoss_Laser_Attach::MidBoss_Laser_Attach()
{
}


MidBoss_Laser_Attach::~MidBoss_Laser_Attach()
{
}

void MidBoss_Laser_Attach::Initialize()
{
}

void MidBoss_Laser_Attach::EnterState()
{
	g_attachDuration = GetFloat(_g_laserAttachDuration);

	m_timer = 0.f;

	auto pivotTr = GetComponent<Enemy_MidBoss>()->GetBulletproofPivot()->GetTransform();

	for (int i = 0; i < 4; ++i)
	{
		m_bulletproof[i] = pivotTr->GetChild(i)->GetComponent<Enemy_BulletProof>();
	}
}

void MidBoss_Laser_Attach::UpdateState()
{
	float inverseRate = 1.f - m_timer / g_attachDuration;
	float sLerpTimer = 1.f - inverseRate * inverseRate;

	for (int i = 0; i < 4; ++i)
	{
		Vector3 startPos = m_bulletproof[i]->GetAttackModePos();
		Vector3 endPos = m_bulletproof[i]->GetShieldModePos();

		m_bulletproof[i]->GetTransform()->position = Nalmak_Math::Lerp(startPos, endPos, sLerpTimer);
	}

	m_timer += dTime;

	if (m_timer >= g_attachDuration)
	{
		SetState(_sn_idle);
		return;
	}
}

void MidBoss_Laser_Attach::ExitState()
{
	GetComponent<Enemy_MidBoss>()->PivotRotateOn();
	GetComponent<Enemy_MidBoss>()->SetRotateSpeed(_SPEED_MID);
}
