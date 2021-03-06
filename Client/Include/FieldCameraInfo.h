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

	// Component��(��) ���� ��ӵ�
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

	// "�ٶ�����ϴ�" Ÿ���� ȸ���ޱ۰�
	Vector3 m_targetAxisAngle = {};

	// "����" Ÿ���� ȸ���ޱ۰�
	Vector3 m_currentAxisAngle = {};

	// Ÿ�ٰ��� �Ÿ�
	float m_targetDistance = 0;


	// ������(�ڽ�)�� �ޱ۰�
	Vector3 m_observerAngle = {};
	// �������� ���� �ޱ۰�
	Vector3 m_observerCurrentAngle = {};

	// y���� 
	float m_yAxisRot = 0.f;
	float m_xAxisRot = 0.f;

	// Ÿ�� ���󰡴� ���ǵ�
	float m_followSpeed = 0.f;

	// ȸ�����ǵ� 
	float m_rotateSpeed = 0.f;

	// z damping speed
	float m_lookSpeed = 0.f;

	//vector3 
	Vector3 m_axisTargetPos = {}; // �� Ÿ�����κ��� �ٶ������ ��ġ



private:
	Transform * m_targetTransform;
	GameObject * m_targetAxis;


};

