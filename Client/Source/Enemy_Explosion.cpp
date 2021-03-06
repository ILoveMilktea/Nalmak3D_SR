#include "stdafx.h"
#include "..\Include\Enemy_Explosion.h"
#include "Enemy.h"
#include "ParticleDead_IfCount0.h"


Enemy_Explosion::Enemy_Explosion()
{
}


Enemy_Explosion::~Enemy_Explosion()
{
}

void Enemy_Explosion::Initialize()
{
}

void Enemy_Explosion::EnterState()
{
	m_pEnemy = m_gameObject->GetComponent<Enemy>();
	assert(L"아 ㅋㅋ 에너미 못 찾은거 같다고 ㅋㅋ" && m_pEnemy);

	m_gameObject->DeleteComponent<VIBufferRenderer>();

	if (m_pExplosionParticle == nullptr)
	{
		m_pExplosionParticle = INSTANTIATE(OBJECT_TAG_PARTICLE, L"enemy_explosion_explosion");

		m_pExplosionParticle->GetTransform()->position = m_transform->position;

		ParticleRenderer::Desc particle_desc;
		particle_desc.particleDataName = L"explosion_Flame";
		particle_desc.PlayOnAwake = true;
		m_pExplosionParticle->AddComponent<ParticleRenderer>(&particle_desc);

		ParticleDead_IfCount0::Desc  dead_desc;
		m_pExplosionParticle->AddComponent<ParticleDead_IfCount0>(&dead_desc);

	}

	if (m_pSmokeParticle == nullptr)
	{
		m_pSmokeParticle = INSTANTIATE(OBJECT_TAG_PARTICLE, L"enemy_explosion_smoke");

		m_pSmokeParticle->GetTransform()->position = m_transform->position;

		ParticleRenderer::Desc smoke_desc;
		smoke_desc.particleDataName = L"explosion_smoke";
		smoke_desc.PlayOnAwake = true;
		m_pSmokeParticle->AddComponent<ParticleRenderer>(&smoke_desc);
		
		ParticleDead_IfCount0::Desc  dead_desc;
		m_pSmokeParticle->AddComponent<ParticleDead_IfCount0>(&dead_desc);
	}


}

void Enemy_Explosion::UpdateState()
{
	//m_pExplosionParticle->GetTransform()->position = m_transform->position;

	//m_pExplosionParticle->GetComponent<ParticleRenderer>()->StopEmit();

	//SetState(L"Death");

	if (m_pExplosionParticle->GetComponent<ParticleRenderer>()->IsPlaying() == false)
	{
		m_pSmokeParticle->GetComponent<ParticleRenderer>()->StopEmit();
		SetState(L"Death");
	}

	DEBUG_LOG(L"Enemy State", L"explosion");
}

void Enemy_Explosion::ExitState()
{
	//m_pExplosionParticle->GetComponent<ParticleRenderer>()->Stop();
}
