#pragma once
#include "Component.h"
class HomingBulletMove :
	public Component
{
public:
	enum AREA { LEFT_TOP, RIGHT_TOP, LEFT_BOTTOM, RIGHT_BOTTOM};

public:
	struct Desc
	{
		GameObject* target = nullptr;

		Vector3 winPos = Vector3(1.f, 0.f, 0.f);
		float speed = 50.f;
		float force = 100.f;
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
};

