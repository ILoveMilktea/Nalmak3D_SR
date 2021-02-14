#include "stdafx.h"
#include "..\Include\PlaneInfo.h"


PlaneInfo::PlaneInfo(Desc * _desc)
{
	m_limitXAngle = _desc->limitXAngle;
	m_limitYAngle = _desc->limitYAngle;
	m_limitZAngle = _desc->limitZAngle;

	m_defaultForce = _desc->defaultForce;


}

PlaneInfo::~PlaneInfo()
{
}

void PlaneInfo::Initialize()
{
}

void PlaneInfo::Update()
{
}

void PlaneInfo::SetXAngle(float _angle)
{
	m_currentXAngle = _angle;

	Nalmak_Math::Clamp(m_currentXAngle, -m_limitXAngle, m_limitXAngle);
}

void PlaneInfo::SetYAngle(float _angle)
{
	m_currentYAngle = _angle;

	Nalmak_Math::Clamp(m_currentYAngle, -m_limitYAngle, m_limitYAngle);
}

void PlaneInfo::SetZAngle(float _angle)
{
	m_currentZAngle = _angle;

	Nalmak_Math::Clamp(m_currentZAngle, -m_limitZAngle, m_limitZAngle);
}

