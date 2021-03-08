#pragma once
#include "IState.h"

class Camera_Boss_Appear :
	public IState
{
public:
	Camera_Boss_Appear();
	virtual ~Camera_Boss_Appear();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:
	const Vector3& RandForShaking();

private:
	//Camera*	m_pMainCamera = nullptr;
	GameObject*	m_pPlayer = nullptr;

	bool	m_bShaking = false;
	bool	m_bProduce = false;
	bool	m_bNext = false;

	Vector3	m_vCameraOrigin = { 0.f,0.f,0.f };
	Vector3 m_vCameraRand = { 0.f,0.f,0.f };
	float	m_fShakingForce = 0.3f;
};

