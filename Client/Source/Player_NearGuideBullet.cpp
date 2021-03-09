#include "stdafx.h"
#include "..\Include\Player_NearGuideBullet.h"
#include "ItemManager.h"

#include "PlayerItem.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Enemy_Boss.h"

#include "PlayerInfoManager.h"
#include "EnemyDetector.h"
#include "ParticleRenderer.h"
#include "ParticleDead_IfCount0.h"

Player_NearGuideBullet::Player_NearGuideBullet(Desc * _desc)
{
	m_firstTarget = _desc->firstTarget;
	m_speed = _desc->speed;
}


Player_NearGuideBullet::~Player_NearGuideBullet()
{
	if (m_smokeParticle)
	{
		m_smokeParticle->AddComponent<ParticleDead_IfCount0>();
		m_smokeParticle->StopEmit();
		m_smokeParticle = nullptr;
	}


	m_gameObject = nullptr;
}

void Player_NearGuideBullet::Initialize()
{
	//effect Start!

	ParticleRenderer::Desc render;
	render.particleDataName = L"missile_smokeLaunch";
	auto obj = INSTANTIATE()->AddComponent<ParticleRenderer>(&render)->AddComponent<ParticleDead_IfCount0>();
	obj->GetComponent<ParticleRenderer>()->Play();
	obj->SetParents(m_gameObject);


	m_firstDir = m_firstTarget - m_transform->position;
	D3DXVec3Normalize(&m_firstDir, &m_firstDir);
	m_player = PlayerInfoManager::GetInstance()->GetPlayer();
	m_enemyDetector = Core::GetInstance()->FindObjectByName(OBJECT_TAG_UI, L"detector")->GetComponent<EnemyDetector>();
	m_target = m_enemyDetector->GetLockOnTarget();
	m_finalTargetPos = m_target->GetTransform()->position;
}

void Player_NearGuideBullet::Update()
{

	SmokeCreate(); //awke

	 // ���� ����
	if (Nalmak_Math::Distance(m_player->GetTransform()->position, m_transform->position) > 500.f)
	{
		Boom();
		DESTROY(m_gameObject);
		m_gameObject = nullptr;
	}

	if (!m_bFinish && Nalmak_Math::Distance(m_firstTarget, m_transform->position) > 2.f)
	{

	


		m_transform->position = Nalmak_Math::Lerp(m_transform->position, m_firstTarget, dTime * 5.f);
		m_transform->LookAt(m_firstDir + m_transform->position, 1.f);

	}
	else
	{
		m_bFinish = true;
	}

	if (!m_bFinish)
		return;

	
	if (Nalmak_Math::Distance(m_finalTargetPos, m_transform->position) > 5.f)
	{
		if (m_target)
		{
			Vector3 toDistance = m_finalTargetPos - m_transform->position;
			D3DXVec3Normalize(&toDistance, &toDistance);
			m_transform->position = Nalmak_Math::Lerp(m_transform->position, m_finalTargetPos, dTime * 3.f);
			m_transform->LookAt(toDistance + m_transform->position, 5.5f);
		}
	
	}
	else if(Nalmak_Math::Distance(m_finalTargetPos, m_transform->position) <= 5.f)
	{
		m_target = nullptr;
	}

	if (!m_target)
	{
		m_transform->position += m_transform->GetForward() * 45 * dTime;
		m_transform->LookAt(m_transform->GetForward() + m_transform->position, 5.5f);
	}
	

}

void Player_NearGuideBullet::Release()
{
}

void Player_NearGuideBullet::OnTriggerEnter(Collisions & _collision)
{

	m_dmg = ItemManager::GetInstance()->FindItemObject(L"Weapon", L"ClusterMissile")->GetItmeInfo().weaponAttak;

	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_ENEMY)
		{
			obj.GetGameObject()->GetComponent<Enemy>()->Damaged(m_dmg);

			Boom();
			DESTROY(m_gameObject);
			m_gameObject = nullptr;
		}

		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_BOSS)
		{
			obj.GetGameObject()->GetComponent<Boss>()->Damaged(m_dmg);

			Boom();
			DESTROY(m_gameObject);
			m_gameObject = nullptr;

		}
	}
}

void Player_NearGuideBullet::OnTriggerStay(Collisions & _collision)
{
}

void Player_NearGuideBullet::OnTriggerExit(Collisions & _collision)
{
}

void Player_NearGuideBullet::Boom()
{
	Vector3 pos = m_transform->GetWorldPosition();
	ParticleRenderer::Desc particle;
	particle.particleDataName = L"explosion_Flame";
	INSTANTIATE()->AddComponent<ParticleRenderer>(&particle)->AddComponent<ParticleDead_IfCount0>()->SetPosition(pos);
	particle.particleDataName = L"explosion_smokeBomb";
	INSTANTIATE()->AddComponent<ParticleRenderer>(&particle)->AddComponent<ParticleDead_IfCount0>()->SetPosition(pos);
	particle.particleDataName = L"explosion_spark";
	INSTANTIATE()->AddComponent<ParticleRenderer>(&particle)->AddComponent<ParticleDead_IfCount0>()->SetPosition(pos);
}

void Player_NearGuideBullet::SmokeCreate()
{
	if (!m_bState)
	{
		ParticleRenderer::Desc render;
		render.particleDataName = L"missile_smoke";
		auto obj = INSTANTIATE()->AddComponent<ParticleRenderer>(&render);
		m_smokeParticle = obj->GetComponent<ParticleRenderer>();
		obj->SetParents(m_gameObject);

		m_bState = true;
	}
}


