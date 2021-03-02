#include "stdafx.h"
#include "..\Include\GarageSceneCameraInfo.h"


GarageSceneCameraInfo::GarageSceneCameraInfo(Desc * _desc)
{
	m_xTargetAxisAngle = 0;
	m_yTargetAxisAngle = 0;
	m_xCurrentAxisAngle = 30;
	m_yCurrentAxisAngle = 50;
	m_targetDistance = -100;
	m_xTargetAngle = 0;
	m_yTargetAngle = 0;
	m_xCurrentAngle = 0;
	m_yCurrentAngle = 0;
	m_yAxisRot = 0;
	m_followSpeed = 0;
	m_rotateSpeed = 0;
	m_lookSpeed = 0;
	m_axisTargetPos = Vector3(0, 5, 0);
	
}

GarageSceneCameraInfo::~GarageSceneCameraInfo()
{
}

void GarageSceneCameraInfo::Initialize()
{
	m_player = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER)->GetTransform();

	m_transform->position = Vector3(0, 0, -100);
	m_transform->SetRotation(-30,30,0);

	m_playerAxis = INSTANTIATE()->SetPosition(m_player->position + m_axisTargetPos);
	m_transform->SetParents(m_playerAxis);
}

void GarageSceneCameraInfo::Update()
{
	m_transform->position = Nalmak_Math::Lerp(m_transform->position, Vector3(0, 0, m_targetDistance), dTime * m_followSpeed); 
	
	m_yTargetAxisAngle += m_yAxisRot * dTime;


	//int cycle = m_yTargetAxisAngle / 360;
	//m_yTargetAxisAngle = m_yTargetAxisAngle - cycle * 360;
	m_xCurrentAxisAngle = Nalmak_Math::Lerp(m_xCurrentAxisAngle, m_xTargetAxisAngle, dTime * m_rotateSpeed);
	m_yCurrentAxisAngle = Nalmak_Math::Lerp(m_yCurrentAxisAngle, m_yTargetAxisAngle, dTime * m_rotateSpeed);
	m_playerAxis->SetRotation(m_xCurrentAxisAngle, m_yCurrentAxisAngle, 0);


	m_xCurrentAngle = Nalmak_Math::Lerp(m_xCurrentAngle, m_xTargetAngle, dTime * m_lookSpeed);
	m_yCurrentAngle = Nalmak_Math::Lerp(m_yCurrentAngle, m_yTargetAngle, dTime * m_lookSpeed);
	m_transform->SetRotation(m_xCurrentAngle, m_yCurrentAngle, 0);


	m_playerAxis->GetTransform()->position = Nalmak_Math::Lerp(m_playerAxis->GetTransform()->position, m_axisTargetPos, dTime * 3);



}

void GarageSceneCameraInfo::SetXAxisAngle(float _angle)
{
	m_xTargetAxisAngle = _angle;
}

void GarageSceneCameraInfo::SetYAxisAngle(float _angle)
{
	m_yTargetAxisAngle = _angle;
}

void GarageSceneCameraInfo::SetXMyAngle(float _angle)
{
	m_xTargetAngle = _angle;
}

void GarageSceneCameraInfo::SetYMyAngle(float _angle)
{
	m_yTargetAngle = _angle;
}

void GarageSceneCameraInfo::SetDistance(float _distance)
{
	m_targetDistance = _distance;
}

void GarageSceneCameraInfo::RotateYAxisAngle(float _angle)
{
	m_yAxisRot = _angle;
}

void GarageSceneCameraInfo::SetFollowSpeed(float _speed)
{
	m_followSpeed = _speed;
}

void GarageSceneCameraInfo::SetRotateSpeed(float _speed)
{
	m_rotateSpeed = _speed;
}

void GarageSceneCameraInfo::SetLookSpeed(float _speed)
{
	m_lookSpeed = _speed;
}

void GarageSceneCameraInfo::SetAxisTargetPos(const Vector3 & _pos)
{
	m_axisTargetPos = _pos;
}

void GarageSceneCameraInfo::AddXAxisAngle(float _angle)
{
	m_xTargetAxisAngle += _angle;
	m_xTargetAxisAngle = Nalmak_Math::Clamp(m_xTargetAxisAngle ,-40.f, 40.f);
}

void GarageSceneCameraInfo::AddYAxisAngle(float _angle)
{
	m_yTargetAxisAngle += _angle;
}

float GarageSceneCameraInfo::GetXAxisAngle()
{
	return m_xCurrentAxisAngle;
}

float GarageSceneCameraInfo::GetYAxisAngle()
{
	return m_yCurrentAxisAngle;
}

float GarageSceneCameraInfo::GetXMyAngle()
{
	return m_xCurrentAngle;
}

float GarageSceneCameraInfo::GetYMyAngle()
{
	return m_yCurrentAngle;
}

float GarageSceneCameraInfo::GetDistance()
{
	return m_targetDistance;
}
