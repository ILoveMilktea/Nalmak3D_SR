#pragma once
#include "IState.h"
class Enemy_Explosion :
	public IState
{
public:
	Enemy_Explosion();
	virtual ~Enemy_Explosion();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:
	class Enemy* m_pEnemy = nullptr;

	GameObject* m_pExplosionParticle = nullptr;
	GameObject*	m_pSmokeParticle = nullptr;
};

