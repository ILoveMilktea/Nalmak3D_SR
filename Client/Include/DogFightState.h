#pragma once
#include "IState.h"
class DogFightState : public IState
{
public:
	DogFightState();
	~DogFightState();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:
	void SceneToEvasion();

	void Player_Faraway();
	void Accelerate();

private:
	GameObject* m_Player = nullptr;
	GameObject* m_MainCamera = nullptr;

	Vector3 vPlayerOrigin;
	bool m_bProduce = false;
	float m_fSpd = 0.f;
};

