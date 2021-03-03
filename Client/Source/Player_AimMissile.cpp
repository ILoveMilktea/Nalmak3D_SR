#include "stdafx.h"
#include "..\Include\Player_AimMissile.h"

Player_AimMissile::Player_AimMissile(Desc * _desc)
{
	m_speed = _desc->speed;
	m_lastPlayerVelocity = _desc->lastPlayerVelocity;

}

Player_AimMissile::~Player_AimMissile()
{
}

void Player_AimMissile::Initialize()
{
	m_fallingTimer = 0.5f; 

	m_dir = m_transform->GetForward();
}

void Player_AimMissile::Update()
{
	if (m_fallingTimer > 0.f)
	{
		m_transform->position -= (m_lastPlayerVelocity + Vector3(0, 5.f, 0)) * dTime;
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
	{
		ParticleRenderer::Desc render;
		render.particleDataName = L"missile_smokeLaunch";
		AddComponent<ParticleRenderer>(&render);
		m_smokeLaunchParticle = GetComponent<ParticleRenderer>();
		m_smokeLaunchParticle->Play();
	}

	{
		ParticleRenderer::Desc render;
		render.particleDataName = L"missile_smoke";
		AddComponent<ParticleRenderer>(&render);
	
	}

	

	
}

void Player_AimMissile::Fly()
{
	m_transform->position += m_dir * m_speed * dTime;
}

void Player_AimMissile::Action()
{
}

void Player_AimMissile::Bomb()
{
	if (m_smokeParticle)
	{
		DESTROY(m_smokeParticle->GetGameObject());
		m_smokeParticle = nullptr;
	}

	if (m_smokeLaunchParticle)
	{
		DESTROY(m_smokeLaunchParticle->GetGameObject());
		m_smokeLaunchParticle = nullptr;
	}
}

void Player_AimMissile::OnTriggerEnter(Collisions & _collision)
{
	Bomb();

	
	DESTROY(m_gameObject);
}

void Player_AimMissile::OnTriggerStay(Collisions & _collision)
{
}

void Player_AimMissile::OnTriggerExit(Collisions & _collision)
{
}
