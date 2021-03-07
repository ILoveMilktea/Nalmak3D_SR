#include "stdafx.h"
#include "..\Include\MidBoss_Sweep_Right.h"

#include "MidBoss_Define.h"
#include "MidBoss_SingleBullet.h"

MidBoss_Sweep_Right::MidBoss_Sweep_Right()
{
}


MidBoss_Sweep_Right::~MidBoss_Sweep_Right()
{
}

void MidBoss_Sweep_Right::Initialize()
{
}

void MidBoss_Sweep_Right::EnterState()
{
	g_patternDuration = GetFloat(_g_sweepDuration);
	g_patternTimer = GetFloat(_g_sweepPatternTimer);
	g_moveRange = GetFloat(_g_sweepMoveRange);

	g_fireTimer = GetFloat(_g_sweepFireTimer);
	g_fireTerm = GetFloat(_g_sweepFireTerm);
	g_branchCount = GetInteger(_g_sweepBranchCount);

	m_lerpDuration = 2.5f;

	if (GetInteger(_g_sweepIsFirstMove))
	{
		float curMoveRange = m_transform->position.x - (_MIDBOSS_CENTERPOS.x - g_moveRange * 0.5f);
		float moveRate = curMoveRange / g_moveRange;

		m_lerpTimer = m_lerpDuration * moveRate;
	}
	else
	{
		m_lerpTimer = 0.f;
	}


	m_startPos = m_transform->position;
}

void MidBoss_Sweep_Right::UpdateState()
{
	g_fireTimer += dTime;
	// attack
	if (g_fireTimer >= g_fireTerm)
	{
		SweepAttack();
		g_fireTimer = 0.f;
	}

	m_lerpTimer += dTime;

	// time over
	if (m_lerpTimer >= m_lerpDuration)
	{
		m_transform->position.x = _MIDBOSS_CENTERPOS.x + g_moveRange * 0.5f;
		SetState(_sn_sweepLeft);
		return;
	}

	float timeRate = m_lerpTimer / m_lerpDuration;
	float radian = PI * (1.f * timeRate);

	m_transform->position.x = _MIDBOSS_CENTERPOS.x  - (0.5f * g_moveRange * (cosf(radian)));

	// limit range over
	if (m_transform->position.x >= _MIDBOSS_CENTERPOS.x + g_moveRange * 0.5f)
	{
		m_transform->position.x = _MIDBOSS_CENTERPOS.x + g_moveRange * 0.5f;
		SetState(_sn_sweepLeft);
		return;
	}

	g_patternTimer += dTime;
	// pattern Time over
	if (g_patternTimer >= g_patternDuration)
	{
		SetState(_sn_idle);
		return;
	}

}

void MidBoss_Sweep_Right::ExitState()
{
	SetFloat(_g_sweepFireTimer, g_fireTimer);
	SetFloat(_g_sweepPatternTimer, g_patternTimer);

	SetInteger(_g_sweepIsFirstMove, false);
}

void MidBoss_Sweep_Right::SweepAttack()
{
	float bossWidth = m_transform->scale.x;
	float muzzleInterval = bossWidth / (g_branchCount - 1);
	
	for (int i = 0; i < g_branchCount; ++i)
	{
		float muzzlePosX = m_transform->position.x - (bossWidth * 0.5f) + muzzleInterval * i;

		auto bullet = INSTANTIATE(OBJECT_TAG_BULLET_ENEMY, L"bullet");
		VIBufferRenderer::Desc meshInfo;
		meshInfo.meshName = L"quadNoneNormal";
		meshInfo.mtrlName = L"fx_20mmCannon";

		SphereCollider::Desc desc_col;
		desc_col.collisionLayer = COLLISION_LAYER_BULLET_ENEMY;
		desc_col.radius = 1.f;

		MidBoss_SingleBullet::Desc bulletinfo;
		bulletinfo.lifeTime = 5.f;
		bulletinfo.speed = 50.f;
		bulletinfo.stretchRatio = 1.f;
		bulletinfo.dmg = 10.f;
		bulletinfo.direction = Vector3(0.f, 0.f, -1.f);

		bullet->AddComponent<VIBufferRenderer>(&meshInfo);
		bullet->AddComponent<SphereCollider>(&desc_col);
		bullet->AddComponent<MidBoss_SingleBullet>(&bulletinfo);

		Vector3 muzzlePos = Vector3(muzzlePosX, m_transform->position.y, m_transform->position.z);
		bullet->SetPosition(muzzlePos);
		bullet->SetScale(1.f, 1.f, 1.f);
	}
}
