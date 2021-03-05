#include "stdafx.h"
#include "..\Include\FieldCameraInfo.h"




FieldCameraInfo::FieldCameraInfo(Desc * _desc)
{
}

FieldCameraInfo::~FieldCameraInfo()
{
}

void FieldCameraInfo::Initialize()
{
	 // 처음은 플레이어로
	m_targetTransform = PlayerInfoManager::GetInstance()->GetPlayer()->GetTransform();
	m_transform->position = Vector3(0, 0, -50);
	m_transform->SetRotation(0, 0, 0);

	m_targetAxis = INSTANTIATE()->SetPosition(m_targetTransform->position );
	m_transform->SetParents(m_targetAxis);
}

void FieldCameraInfo::Update()
{
	
	m_targetAxisAngle.x += m_xAxisRot * dTime;
	m_targetAxisAngle.y += m_yAxisRot * dTime;

	m_currentAxisAngle.x = Nalmak_Math::Lerp(m_currentAxisAngle.x, m_targetAxisAngle.x, dTime * m_rotateSpeed);
	m_currentAxisAngle.y = Nalmak_Math::Lerp(m_currentAxisAngle.y, m_targetAxisAngle.y, dTime * m_rotateSpeed);
	m_currentAxisAngle.z = Nalmak_Math::Lerp(m_currentAxisAngle.z, m_targetAxisAngle.z, dTime * m_rotateSpeed);
	m_targetAxis->SetRotation(m_currentAxisAngle.x, m_currentAxisAngle.y , m_currentAxisAngle.z);


	// 자식 
	m_observerCurrentAngle.x = Nalmak_Math::Lerp(m_observerCurrentAngle.x, m_observerAngle.x, dTime * m_lookSpeed);
	m_observerCurrentAngle.y = Nalmak_Math::Lerp(m_observerCurrentAngle.y, m_observerAngle.y, dTime * m_lookSpeed);
	m_observerCurrentAngle.z = Nalmak_Math::Lerp(m_observerCurrentAngle.z, m_observerAngle.z, dTime * m_lookSpeed);
	
	m_transform->position.x = Nalmak_Math::Lerp(m_transform->position.x, 0.f, dTime * m_followSpeed);
	m_transform->position.y = Nalmak_Math::Lerp(m_transform->position.y, 0.f, dTime * m_followSpeed);
	m_transform->position.z = Nalmak_Math::Lerp(m_transform->position.z, -m_targetDistance, dTime * m_followSpeed);

	m_transform->SetRotation(m_observerCurrentAngle.x, m_observerCurrentAngle.y, 0.f);
	DEBUG_LOG(L"로컬", m_transform->position);
	DEBUG_LOG(L"월드", m_transform->GetWorldPosition());


	Matrix test = m_transform->GetWorldMatrix();

	m_targetAxis->GetTransform()->position = Nalmak_Math::Lerp(m_targetAxis->GetTransform()->position, m_axisTargetPos, dTime * m_followSpeed);

}

void FieldCameraInfo::SetXAxisAngle(float _angle)
{
	m_targetAxisAngle.x = _angle;
}

void FieldCameraInfo::SetYAxisAngle(float _angle)
{
	m_targetAxisAngle.y = _angle;
}

void FieldCameraInfo::SetZAxisAngle(float _angle)
{
	m_targetAxisAngle.z = _angle;
}

void FieldCameraInfo::SetXMyAngle(float _angle)
{
	m_observerAngle.x = _angle;
}

void FieldCameraInfo::SetYMyAngle(float _angle)
{
	m_observerAngle.y = _angle;
}

void FieldCameraInfo::SetZMyAngle(float _angle)
{
	m_observerAngle.z = _angle;
}

void FieldCameraInfo::SetDistance(float _distance)
{
	m_targetDistance = _distance;
}

void FieldCameraInfo::RotateXAxisAngle(float _angle)
{
	m_xAxisRot = _angle;
}

void FieldCameraInfo::RotateYAxisAngle(float _angle)
{
	m_yAxisRot = _angle;
}

void FieldCameraInfo::SetFollowSpeed(float _speed)
{
	m_followSpeed = _speed;
}

void FieldCameraInfo::SetRotateSpeed(float _speed)
{
	m_rotateSpeed = _speed;
}

void FieldCameraInfo::SetLookSpeed(float _speed)
{
	m_lookSpeed = _speed;
}

void FieldCameraInfo::SetAxisTargetPos(const Vector3 & _pos)
{
	m_axisTargetPos = _pos;
}

void FieldCameraInfo::AddXAxisAngle(float _angle)
{
	m_targetAxisAngle.x += _angle;
}

void FieldCameraInfo::AddYAxisAngle(float _angle)
{
	m_targetAxisAngle.y += _angle;
}

void FieldCameraInfo::AddZAxisAngle(float _angle)
{
	m_targetAxisAngle.z += _angle;
}

void FieldCameraInfo::AddDistance(float _distance)
{
	m_targetDistance += _distance;
}

void FieldCameraInfo::Reset()
{
	m_targetAxis->SetRotation(0, 0, 0);

	m_currentAxisAngle = {0,0,0};
	m_observerCurrentAngle = {0,0,0};

	
	m_axisTargetPos = {0,0,0};
	m_targetDistance = 0;
}

void FieldCameraInfo::SetTarget(Transform * _targetTransform)
{
	m_targetTransform = _targetTransform;
}
////////////////////////////////////////////////////////////////////////


float FieldCameraInfo::GetXAxisAngle()
{
	return m_currentAxisAngle.x;
}

float FieldCameraInfo::GetYAxisAngle()
{
	return m_currentAxisAngle.y;
}

float FieldCameraInfo::GetZAxisAngle()
{
	return m_currentAxisAngle.z;
}

float FieldCameraInfo::GetXMyAngle()
{
	return m_observerCurrentAngle.x;
}

float FieldCameraInfo::GetYMyAngle()
{
	return m_observerCurrentAngle.y;
}

float FieldCameraInfo::GetZMyAngle()
{
	return m_observerCurrentAngle.z;
}

float FieldCameraInfo::GetDistance()
{
	return m_targetDistance;
}
