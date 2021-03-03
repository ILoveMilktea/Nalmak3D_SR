#include "stdafx.h"
#include "StageSelectCamera.h"
#include "StageSelectSceneManager.h"
#include "MoveBySpline.h"

StageSelectCamera::StageSelectCamera(Desc * _desc)
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

StageSelectCamera::~StageSelectCamera()
{
}

void StageSelectCamera::Initialize()
{
	
	m_transform->position = Vector3(0, 0, -100);
	m_transform->SetRotation(-30, 30, 0);

	m_playerAxis = INSTANTIATE()->SetPosition(m_axisTargetPos);
	m_transform->SetParents(m_playerAxis);
}

void StageSelectCamera::Update()
{
	m_transform->position = Nalmak_Math::Lerp(m_transform->position, Vector3(0, 0, m_targetDistance), dTime * m_followSpeed);

	m_yTargetAxisAngle += m_yAxisRot * dTime;

	m_yCurrentAxisAngle = Nalmak_Math::Lerp(m_yCurrentAxisAngle, m_yTargetAxisAngle, dTime * m_rotateSpeed);
	m_xCurrentAxisAngle = Nalmak_Math::Lerp(m_xCurrentAxisAngle, m_xTargetAxisAngle, dTime * m_rotateSpeed);
	m_playerAxis->SetRotation(m_xCurrentAxisAngle, m_yCurrentAxisAngle, 0);


	m_xCurrentAngle = Nalmak_Math::Lerp(m_xCurrentAngle, m_xTargetAngle, dTime * m_lookSpeed);
	m_yCurrentAngle = Nalmak_Math::Lerp(m_yCurrentAngle, m_yTargetAngle, dTime * m_lookSpeed);
	m_transform->SetRotation(m_xCurrentAngle, m_yCurrentAngle, 0);


	m_playerAxis->GetTransform()->position = Nalmak_Math::Lerp(m_playerAxis->GetTransform()->position, m_axisTargetPos, dTime * 3);
}

void StageSelectCamera::SetXAxisAngle(float _angle)
{
	m_xTargetAxisAngle = _angle;
}

void StageSelectCamera::SetYAxisAngle(float _angle)
{
	m_yTargetAxisAngle = _angle;
}

void StageSelectCamera::SetXMyAngle(float _angle)
{
	m_xTargetAngle = _angle;
}

void StageSelectCamera::SetYMyAngle(float _angle)
{
	m_yTargetAngle = _angle;
}

void StageSelectCamera::SetDistance(float _distance)
{
	m_targetDistance = _distance;
}

void StageSelectCamera::RotateYAxisAngle(float _angle)
{
	m_yAxisRot = _angle;
}

void StageSelectCamera::SetFollowSpeed(float _speed)
{
	m_followSpeed = _speed;
}

void StageSelectCamera::SetRotateSpeed(float _speed)
{
	m_rotateSpeed = _speed;
}

void StageSelectCamera::SetLookSpeed(float _speed)
{
	m_lookSpeed = _speed;
}

void StageSelectCamera::SetAxisTargetPos(const Vector3 & _pos)
{
	m_axisTargetPos = _pos;
}

void StageSelectCamera::AddXAxisAngle(float _angle)
{
	m_xTargetAxisAngle += _angle;
	m_xTargetAxisAngle = Nalmak_Math::Clamp(m_xTargetAxisAngle, -40.f, 40.f);
}

void StageSelectCamera::AddYAxisAngle(float _angle)
{
	m_yTargetAxisAngle += _angle;
}

void StageSelectCamera::AddDistance(float _distance)
{
	m_targetDistance += _distance;
	m_targetDistance = Nalmak_Math::Clamp(m_targetDistance, -30.f, -7.f);
}

float StageSelectCamera::GetXAxisAngle()
{
	return m_xCurrentAxisAngle;
}

float StageSelectCamera::GetYAxisAngle()
{
	return m_yCurrentAxisAngle;
}

float StageSelectCamera::GetXMyAngle()
{
	return m_xCurrentAngle;
}

float StageSelectCamera::GetYMyAngle()
{
	return m_yCurrentAngle;
}

float StageSelectCamera::GetDistance()
{
	return m_targetDistance;
}

bool StageSelectCamera::IsNearToTarget()
{
	return  Nalmak_Math::DistanceSq(m_axisTargetPos,m_playerAxis->GetTransform()->position) < 2;
}
