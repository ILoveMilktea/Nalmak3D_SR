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
		float speed = 45.f;
		float force = 1000.f;
	};
public:
	HomingBulletMove(Desc* _desc);
	virtual ~HomingBulletMove();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;

private:
	Transform* m_target;
	Rigidbody* m_rigidbody;
	Vector3 m_winPos;
	Vector3 m_moveDir;
	float m_speed;
	float m_force;
	GameObject* m_player;
	Vector3* m_finalPos = nullptr;
	float m_tempTimer;
};

