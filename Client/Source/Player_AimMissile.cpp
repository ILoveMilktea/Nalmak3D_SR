#include "stdafx.h"
#include "..\Include\Player_AimMissile.h"
#include "ParticleDead_IfCount0.h"
#include "ItemManager.h"
#include "Enemy.h"
#include "PlayerItem.h"
#include "Enemy_Boss.h"
Player_AimMissile::Player_AimMissile(Desc * _desc)
{
	m_speed = _desc->speed;
	m_lastPlayerVelocity = _desc->lastPlayerVelocity;
	m_deadTimer = _desc->deadTimer;

}

Player_AimMissile::~Player_AimMissile()
{
}

void Player_AimMissile::Initialize()
{
	m_fallingTimer = 0.3f; 

	m_dir = m_transform->GetForward();
}

void Player_AimMissile::Update()
{
	if (m_fallingTimer > 0.f)
	{
		m_transform->position -= (m_lastPlayerVelocity + Vector3(0, 3.f, 0)) * dTime;
		m_fallingTimer -= dTime;

		if (m_fallingTimer <= 0.f)
		{
			Create();
		}
	}
	else
	{
		Fly();
	}

}

void Player_AimMissile::Release()
{
	
}

void Player_AimMissile::Create()
{
	//{
	//	ParticleRenderer::Desc render;
	//	render.particleDataName = L"missile_smokeLaunch";
	//	auto obj = INSTANTIATE()->AddComponent<ParticleRenderer>(&render)->AddComponent<ParticleDead_IfCount0>();
	//	obj->GetComponent<ParticleRenderer>()->Play();
	//	obj->SetParents(m_gameObject);
	//}

	//{
	//	ParticleRenderer::Desc render;
	//	render.particleDataName = L"missile_smoke";
	//	auto obj = INSTANTIATE()->AddComponent<ParticleRenderer>(&render);
	//	m_smokeParticle = obj->GetComponent<ParticleRenderer>();
	//	obj->SetParents(m_gameObject);
	//}
	{
		PointLight::Desc light;
		light.radius = 15.f;
		light.diffuseIntensity = 2.f;
		light.color = Vector3(1, 0.4f, 0.1f);
		AddComponent<PointLight>(&light);
	}
	

	
}

void Player_AimMissile::Fly()
{
	m_transform->position += m_dir * m_speed * dTime;

	m_deadTimer -= dTime;

	if (m_deadTimer < 0)
	{
		Bomb();
	}
}

void Player_AimMissile::Action()
{
}

void Player_AimMissile::Bomb()
{
	if (m_smokeParticle)
	{
		m_smokeParticle->AddComponent<ParticleDead_IfCount0>();
		m_smokeParticle->StopEmit();
		m_smokeParticle = nullptr;
	}

	//Vector3 pos = m_transform->GetWorldPosition();
	//ParticleRenderer::Desc particle;
	//particle.particleDataName = L"explosion_Flame";
	//INSTANTIATE()->AddComponent<ParticleRenderer>(&particle)->AddComponent<ParticleDead_IfCount0>()->SetPosition(pos);
	//particle.particleDataName = L"explosion_smokeBomb";
	//INSTANTIATE()->AddComponent<ParticleRenderer>(&particle)->AddComponent<ParticleDead_IfCount0>()->SetPosition(pos);
	//particle.particleDataName = L"explosion_spark";
	//INSTANTIATE()->AddComponent<ParticleRenderer>(&particle)->AddComponent<ParticleDead_IfCount0>()->SetPosition(pos);

	DESTROY(m_gameObject);
	m_gameObject = nullptr;

}

void Player_AimMissile::OnTriggerEnter(Collisions & _collision)
{
	int iDmg = ItemManager::GetInstance()->FindItemObject(L"Weapon", L"AimMissile")->GetItmeInfo().weaponAttak;

	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_ENEMY)
		{
			obj.GetGameObject()->GetComponent<Enemy>()->Damaged(iDmg);

			DESTROY(m_gameObject);
			m_gameObject = nullptr;
		}

		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_BOSS)
		{
			obj.GetGameObject()->GetComponent<Boss>()->Damaged(iDmg);

			DESTROY(m_gameObject);
			m_gameObject = nullptr;
		}
	}
	
}

void Player_AimMissile::OnTriggerStay(Collisions & _collision)
{
}

void Player_AimMissile::OnTriggerExit(Collisions & _collision)
{
}
