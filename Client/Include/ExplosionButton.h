#pragma once
#include "Component.h"
class ExplosionButton :
	public Component
{
public:
	struct Desc
	{

	};
public:
	ExplosionButton(Desc* _desc);
	~ExplosionButton();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;

private:
	ParticleRenderer* m_particles[4];
};

