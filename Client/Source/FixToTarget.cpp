#include "stdafx.h"
#include "..\Include\FixToTarget.h"

FixToTarget::FixToTarget(Desc * _desc)
{
	m_fromObject = _desc->obj;
	//m_addPosition = _desc->addPosition;

	m_followDistance = _desc->distanceAngle;
	m_height = _desc->height;
	m_distanceAngle = _desc->distanceAngle;
}

FixToTarget::~FixToTarget()
{
}

void FixToTarget::Initialize()
{
}

void FixToTarget::Update()
{
	m_fromObject->SetPosition(m_transform->position + Vector3(0, m_height, -m_followDistance));
	m_fromObject->SetRotation(m_distanceAngle, 0.f, 0.f);

}
