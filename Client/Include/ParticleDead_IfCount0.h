#pragma once
#include "Component.h"
class ParticleDead_IfCount0 :
	public Component
{
public:
	struct Desc
	{

	};
public:
	ParticleDead_IfCount0(Desc* _desc);
	~ParticleDead_IfCount0();

	virtual void Initialize() override;
	virtual void Update() override;
	
private:
	ParticleRenderer* m_particle;

};

