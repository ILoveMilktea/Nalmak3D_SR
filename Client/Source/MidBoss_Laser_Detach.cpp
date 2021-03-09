#include "stdafx.h"
#include "..\Include\MidBoss_Laser_Detach.h"

#include "MidBoss_Define.h"
#include "Enemy_MidBoss.h"
#include "Enemy_BulletProof.h"

MidBoss_Laser_Detach::MidBoss_Laser_Detach()
{
}


MidBoss_Laser_Detach::~MidBoss_Laser_Detach()
{
}

void MidBoss_Laser_Detach::Initialize()
{
}

void MidBoss_Laser_Detach::EnterState()
{
	g_detachDuration = GetFloat(_g_laserDetachDuration);

	m_timer = 0.f;

	auto pivotTr = GetComponent<Enemy_MidBoss>()->GetBulletproofPivot()->GetTransform();

	for (int i = 0; i < 4; ++i)
	{
		m_bulletproof[i] = pivotTr->GetChild(i)->GetComponent<Enemy_BulletProof>();
	}
}

void MidBoss_Laser_Detach::UpdateState()
{
	float inverseRate = 1.f - m_timer / g_detachDuration;
	float sLerpTimer = 1.f - inverseRate * inverseRate;

	for (int i = 0; i < 4; ++i)
	{
		Vector3 startPos = m_bulletproof[i]->GetShieldModePos();
		Vector3 endPos = m_bulletproof[i]->GetAttackModePos();

		m_bulletproof[i]->GetTransform()->position = Nalmak_Math::Lerp(startPos, endPos, sLerpTimer);
	}

	m_timer += dTime;

	if (m_timer >= g_detachDuration)
	{
		SetState(_sn_laserCharge);
		return;
	}

}

void MidBoss_Laser_Detach::ExitState()
{
}
