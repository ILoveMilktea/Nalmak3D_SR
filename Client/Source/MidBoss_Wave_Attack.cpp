#include "stdafx.h"
#include "..\Include\MidBoss_Wave_Attack.h"
#include "MidBoss_Define.h"
#include "MidBoss_SingleBullet.h"

MidBoss_Wave_Attack::MidBoss_Wave_Attack()
{
}


MidBoss_Wave_Attack::~MidBoss_Wave_Attack()
{
}

void MidBoss_Wave_Attack::Initialize()
{
}

void MidBoss_Wave_Attack::EnterState()
{
	g_waveAngle = GetFloat(_g_waveAngle);
	g_waveTerm = GetFloat(_g_waveTerm);
	g_waveBulletCount = GetInteger(_g_waveBulletCount);
	g_waveAttackCount = GetInteger(_g_waveAttackCount);

	m_curWaveAttackIndex = 0;
	m_waveTimer = 0.f;

}

void MidBoss_Wave_Attack::UpdateState()
{
	m_waveTimer += dTime;

	if (m_waveTimer > g_waveTerm)
	{
		WaveAttack();
		
		++m_curWaveAttackIndex;
		if (m_curWaveAttackIndex >= g_waveAttackCount)
		{
			SetState(_sn_waveIdle);
			return;
		}

		m_waveTimer = 0.f;
	}


#ifdef _DEBUG
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F9))
	{
		SetState(_sn_idle);
		return;
	}
#endif // _DEBUG
}

void MidBoss_Wave_Attack::ExitState()
{
}

void MidBoss_Wave_Attack::WaveAttack()
{
	for (int i = 0; i < g_waveBulletCount; ++i)
	{
		float fireAngle = g_waveAngle / g_waveBulletCount * i + 220.f;
		fireAngle += (g_waveAngle / g_waveBulletCount) * 0.5f * (m_curWaveAttackIndex % 2);

		auto bullet = INSTANTIATE(OBJECT_TAG_BULLET_ENEMY, L"bullet");
		VIBufferRenderer::Desc meshInfo;
		meshInfo.meshName = L"quadNoneNormal";
		meshInfo.mtrlName = L"fx_20mmCannon";

		SphereCollider::Desc desc_col;
		desc_col.collisionLayer = COLLISION_LAYER_BULLET_ENEMY;
		desc_col.radius = 2.f;

		MidBoss_SingleBullet::Desc bulletinfo;
		bulletinfo.lifeTime = 5.f;
		bulletinfo.speed = 20.f;
		bulletinfo.stretchRatio = 1.f;
		bulletinfo.dmg = 10.f;
		Vector3 dir = Vector3(cosf(Deg2Rad*fireAngle), 0.f, sinf(Deg2Rad*fireAngle));
		D3DXVec3Normalize(&dir, &dir);
		bulletinfo.direction = dir;

		bullet->AddComponent<VIBufferRenderer>(&meshInfo);
		bullet->AddComponent<SphereCollider>(&desc_col);
		bullet->AddComponent<MidBoss_SingleBullet>(&bulletinfo);

		bullet->SetPosition(m_transform->position);
		bullet->SetScale(2.f, 2.f, 2.f);

	}
}
