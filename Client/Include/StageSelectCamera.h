#pragma once
#include "Component.h"

class StageSelectCamera :
	public Component
{
public:
	struct Desc
	{

	};
public:
	StageSelectCamera(Desc* _desc);
	~StageSelectCamera();
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

	float m_xTargetAxisAngle;
	float m_yTargetAxisAngle;
	float m_xCurrentAxisAngle;
	float m_yCurrentAxisAngle;
	float m_targetDistance;

	float m_xTargetAngle;
	float m_yTargetAngle;
	float m_xCurrentAngle;
	float m_yCurrentAngle;


	float m_yAxisRot;
	float m_followSpeed;
	float m_rotateSpeed;
	float m_lookSpeed;

	Vector3 m_axisTargetPos;
public:
	void SetXAxisAngle(float _angle);
	void SetYAxisAngle(float _angle);
	void SetXMyAngle(float _angle);
	void SetYMyAngle(float _angle);
	void SetDistance(float _distance);
	void RotateYAxisAngle(float _angle);
	void SetFollowSpeed(float _speed);
	void SetRotateSpeed(float _speed);
	void SetLookSpeed(float _speed);
	void SetAxisTargetPos(const Vector3& _pos);
	void AddXAxisAngle(float _angle);
	void AddYAxisAngle(float _angle);
	void AddDistance(float _distance);
public:
	float GetXAxisAngle();
	float GetYAxisAngle();
	float GetXMyAngle();
	float GetYMyAngle();
	float GetDistance();
	bool IsNearToTarget();

private:
	GameObject* m_playerAxis;
};

