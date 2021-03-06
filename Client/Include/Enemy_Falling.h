#pragma once
#include "IState.h"
class Enemy_Falling :
	public IState
{
public:
	Enemy_Falling();
	virtual ~Enemy_Falling();

	// IState��(��) ���� ��ӵ�

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

	

public:

public:
	void Accelerate();

private:
	class Enemy* m_pEnemy = nullptr;
	
	//bool		m_bToGournd = true;
	//bool		m_bFalling = false;
	float		m_fFallDelta = 0.f;
	float		m_fFallingSpd = 0.f;
	float		m_fTurnSpd = 0.f;

	GameObject* m_pSmokeParticle = nullptr;
};

