#pragma once
#include "Component.h"
class Indicator_EnemyPos :
	public Component
{
public:
	struct Desc
	{
		GameObject* Target = nullptr;
		float fDist = 5.0f;

	};
public:
	Indicator_EnemyPos(Desc* _desc);
	virtual ~Indicator_EnemyPos();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate()override;

public:
	void Release_Target();

private:
	Camera*		m_pMainCamera = nullptr;
	GameObject* m_pTarget = nullptr;
	GameObject* m_pPlayer = nullptr;

	Material*	m_pAlpha = nullptr;

	Vector3		m_vForward;
	Vector3		m_vDir;
	float		m_fDist = 0.f;
};

