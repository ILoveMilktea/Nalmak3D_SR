#pragma once

#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__

#include "Component.h"
class NALMAK_DLL Rigidbody :
	public Component
{
public:
	struct Desc
	{
		float mass = 10.f;							// 질량
		float dragCoefficient = 0.04f;				// 유선형 기체의 저항계수? https://t1.daumcdn.net/cfile/tistory/990E98405D352AA208
		float gravityDragCoefficient = 0.42f;
		float torqueDragCoefficient = 0.2f;
		float radius = 5.f;							// 구체 반지름
		float gravityRate = 1.f;					// 중력 비율

		bool isGravity = true;
		bool isAirDrag = false;
		bool isGravityDrag = false;
		bool isTorqueDrag = true;
	};
public:
	Rigidbody(Desc* _desc);
	~Rigidbody();
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate()override;

	void IntegrateForce(float deltaTime);			// 힘 -> 속도
	void IntegrateAngularForce(float deltaTime);	// torque -> 각속도

private:
	Vector3 m_position;			// rigidbody의 position, transform position (before new update)
	float m_inverseMass;		// 질량의 역수
	float m_airDragCoefficient;	// 정면 공기 저항 계수
	float m_gravityDragCoefficient;// 중력 저항 계수 (구체)

	Vector3 m_force;			// 받는 외부힘
	Vector3 m_dragForce;		// 저항 힘
	Vector3 m_velocity;			// 선속도

	Vector3 m_torque;			// 토크, 회전력?
	Vector3 m_dragTorque;		// 저항 토크
	Vector3 m_angularVelocity;	// 각속도
	float m_InverseInertia;		// 관성 텐서???
	float m_torqueDragCoefficient; // 회전 저항 계수 -> 지금 임의값

	bool m_isGravity;			// 중력 on, off
	bool m_isAirDrag;			// 공기저항 on, off
	bool m_isGravityDrag;		// 중력저항 on, off
	bool m_isTorqueDrag;		// 회전저항 on, off

	float m_gravityRate;

public:
	void SetForce(const Vector3& _force) { m_force = _force; }
	void AddForce(const Vector3& _force) { m_force += _force; }		// AddForce는 어디선가 외부에서 한다
	void AddForceForward(float _power);

	void SetVelocity(const Vector3& _velocity) { m_velocity = _velocity; }
	void SetVelocityX(const float& _x) { m_velocity.x = _x; }
	void SetVelocityY(const float& _y) { m_velocity.y = _y; }
	void SetVelocityZ(const float& _z) { m_velocity.z = _z; }

	void AddTorque(const Vector3& _torque) { m_torque += _torque; }
	void SetAngularVelocity(const Vector3& _velocity) { m_angularVelocity = _velocity; }

	void SetActiveGravity(bool _active) { m_isGravity = _active; }
	void SetActiveAirDrag(bool _active) { m_isAirDrag = _active; }
	void SetActiveGravityDrag(bool _active) { m_isGravityDrag = _active; }

public:
	const Vector3& GetForce() { return m_force; }
	const Vector3& GetVelocity() { return m_velocity; }

	const Vector3& GetTorque() { return m_torque; }
	const Vector3& GetAngularVelocity() { return m_angularVelocity; }

};

#endif // !__RIGIDBODY_H__
