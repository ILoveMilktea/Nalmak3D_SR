#pragma once
#include "Component.h"
class Enemy_BulletProof :
	public Component
{
public:
	struct Desc
	{
		Desc(ENEMY_STATUS _status)
		{
			tStatus = _status;
		}
		ENEMY_STATUS tStatus;


		Vector3 shieldModePos;
		Vector3 attackModePos;
	};

public:
	Enemy_BulletProof(Desc* _desc);
	~Enemy_BulletProof();

	virtual void Initialize() override;
	virtual void Update() override;

	const Vector3& GetShieldModePos() { return m_shieldModePos; }
	const Vector3& GetAttackModePos() { return m_attackModePos; }

private:
	Vector3 m_shieldModePos;
	Vector3 m_attackModePos;
};

