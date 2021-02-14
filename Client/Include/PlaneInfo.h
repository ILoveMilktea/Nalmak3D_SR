#pragma once
#include "Component.h"
class PlaneInfo :
	public Component
{
public:
	struct Desc {
		float limitXAngle = 15.f;
		float limitYAngle = 15.f;
		float limitZAngle = 15.f;

		Vector3 defaultForce = Vector3(0.f, 0.f, 50.f);
	};
public:
	PlaneInfo(Desc* _desc);
	~PlaneInfo();
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

public: /* Set Info Member */
	void SetXAngle(float _angle);
	void SetYAngle(float _angle); 
	void SetZAngle(float _angle);

	void SetDefaultForce(Vector3 _force) { m_defaultForce = _force; }
	void SetRecoverTorque(Vector3 _torque) { m_recoverTorque = _torque; }

public: /* Get Info Member */
	float GetXAngle() { return m_currentXAngle; }
	float GetYAngle() { return m_currentYAngle; }
	float GetZAngle() { return m_currentZAngle; }

	Vector3 GetDefaultForce() { return m_defaultForce; }
	Vector3 GetRecoverTorque() { return m_recoverTorque; }

private:
	// 회전 각 제한
	float m_currentXAngle = 0;
	float m_currentYAngle = 0;
	float m_currentZAngle = 0;

	float m_limitXAngle;
	float m_limitYAngle;
	float m_limitZAngle;


	// default forward force
	Vector3 m_defaultForce;
	// recover rotation
	Vector3 m_recoverTorque;

	//체력
	//탄창
	// 상수값
	// 적도 이거씀

};

