#include "stdafx.h"
#include "..\Include\ParticleDead_IfCount0.h"


ParticleDead_IfCount0::ParticleDead_IfCount0(Desc * _desc)
{
}

ParticleDead_IfCount0::~ParticleDead_IfCount0()
{
}

void ParticleDead_IfCount0::Initialize()
{
	m_particle = GetComponent<ParticleRenderer>();
}

void ParticleDead_IfCount0::Update()
{
	if (m_particle->GetActivedParticleCount() == 0 && !m_particle->IsPlaying())
	{
		DESTROY(m_gameObject);
	}
}
