#include "PointLight.h"
#include "Transform.h"


PointLight::PointLight(Desc * _desc)
{
	m_lightInfo.base.color = _desc->color;
	m_lightInfo.base.ambientIntensity = _desc->ambientIntensity;
	m_lightInfo.base.diffuseIntensity = _desc->diffuseIntensity;

	m_lightInfo.constant = _desc->constant;
	m_lightInfo.exp = _desc->exp;
	m_lightInfo.linearRatio = _desc->linearRatio;

	m_lightMode = LIGHT_MODE_POINT;
}

PointLight::~PointLight()
{
}

void PointLight::Initialize()
{
	m_lightManager->AddPointLight(this);
}

void PointLight::Update()
{
}

void PointLight::PreRender()
{
	//m_lightInfo.position = m_transform->GetWorldPosition();
}


float PointLight::GetRadius()
{
	float maxChannel = fmax(fmax(m_lightInfo.base.color.x, m_lightInfo.base.color.y), m_lightInfo.base.color.z);

	float radius = (-m_lightInfo.linearRatio + sqrtf(m_lightInfo.linearRatio * m_lightInfo.linearRatio -
		4 * m_lightInfo.exp * (m_lightInfo.exp - 256 * maxChannel * m_lightInfo.base.diffuseIntensity)))
		/
		(2 * m_lightInfo.exp);

	return radius;
}


void PointLight::Release()
{
	m_lightManager->DeletePointLight(this);
}


