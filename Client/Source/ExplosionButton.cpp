#include "stdafx.h"
#include "ExplosionButton.h"
#include "..\Include\ExplosionButton.h"




ExplosionButton::ExplosionButton(Desc * _desc)
{
}

ExplosionButton::~ExplosionButton()
{
}

void ExplosionButton::Initialize()
{
	ParticleRenderer::Desc particle;
	particle.particleDataName = L"explosion_Flame";
	auto particle0 = INSTANTIATE()->AddComponent<ParticleRenderer>(&particle)->SetPosition(m_transform->position);
	particle.particleDataName = L"explosion_smoke";
	auto particle1 = INSTANTIATE()->AddComponent<ParticleRenderer>(&particle)->SetPosition(m_transform->position);
	particle.particleDataName = L"explosion_smokeBomb";
	auto particle2 = INSTANTIATE()->AddComponent<ParticleRenderer>(&particle)->SetPosition(m_transform->position);
	particle.particleDataName = L"explosion_spark";
	auto particle3 = INSTANTIATE()->AddComponent<ParticleRenderer>(&particle)->SetPosition(m_transform->position);





	m_particles[0] = particle0->GetComponent<ParticleRenderer>();
	m_particles[1] = particle1->GetComponent<ParticleRenderer>();
	m_particles[2] = particle2->GetComponent<ParticleRenderer>();
	m_particles[3] = particle3->GetComponent<ParticleRenderer>();

}

void ExplosionButton::Update()
{

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		for (int i = 0; i < 4; ++i)
		{
			m_particles[i]->Play();
		}
	}
}
