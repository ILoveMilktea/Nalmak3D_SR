#pragma once
#include "Component.h"
class HomingBulletMove :
	public Component
{
public:
	struct Desc
	{
		GameObject* target = nullptr;

		Vector3 winPos = Vector3(1.f, 0.f, 0.f);
		float speed = 40.f;
		float force = 1000.f;
	};
public:
	HomingBulletMove(Desc* _desc);

	virtual void Initialize() override;
	virtual void Update() override;

private:
	Transform* m_target;
	Rigidbody* m_rigidbody;
	Vector3 m_winPos;
	Vector3 m_moveDir;
	float m_speed;
	float m_force;


	float m_tempTimer;
};

