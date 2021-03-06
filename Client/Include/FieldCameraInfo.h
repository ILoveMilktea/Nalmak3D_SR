#pragma once
#include "Component.h"
class FieldCameraInfo :
	public Component
{
public:
	struct Desc
	{

	};
public:
	FieldCameraInfo(Desc* _desc);
	virtual ~FieldCameraInfo();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
public:
	void SetXAxisAngle(float _angle);
	void SetYAxisAngle(float _angle);
	void SetZAxisAngle(float _angle);

	void SetXMyAngle(float _angle);
	void SetYMyAngle(float _angle);
	void SetZMyAngle(float _angle);


	void SetDistance(float _distance);

	void RotateXAxisAngle(float _angle);
	void RotateYAxisAngle(float _angle);
	
	void SetFollowSpeed(float _speed);
	void SetRotateSpeed(float _speed);
	void SetLookSpeed(float _speed);
	void SetAxisTargetPos(const Vector3& _pos);
	void AddXAxisAngle(float _angle);
	void AddYAxisAngle(float _angle);
	void AddZAxisAngle(float _angle);

	
	void AddDistance(float _distance);
	bool IsNearToTarget();
	//
	void Reset();
	//
	void SetTarget(Transform * _targetTransform);
public: // Getter
	float GetXAxisAngle();
	float GetYAxisAngle();
	float GetZAxisAngle();


	float GetXMyAngle();
	float GetYMyAngle();
	float GetZMyAngle();

	float GetDistance();


private:

	// "바라봐야하는" 타겟의 회전앵글값
	Vector3 m_targetAxisAngle = {};

	// "현재" 타겟의 회전앵글값
	Vector3 m_currentAxisAngle = {};

	// 타겟과의 거리
	float m_targetDistance = 0;


	// 관찰자(자식)의 앵글값
	Vector3 m_observerAngle = {};
	// 관찰자의 현재 앵글값
	Vector3 m_observerCurrentAngle = {};

	// y자전 
	float m_yAxisRot = 0.f;
	float m_xAxisRot = 0.f;

	// 타겟 따라가는 스피드
	float m_followSpeed = 0.f;

	// 회전스피드 
	float m_rotateSpeed = 0.f;

	// z damping speed
	float m_lookSpeed = 0.f;

	//vector3 
	Vector3 m_axisTargetPos = {}; // 본 타겟으로부터 바라봐야할 위치



private:
	Transform * m_targetTransform;
	GameObject * m_targetAxis;


};

