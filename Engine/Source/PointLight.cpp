#include "..\Include\PointLight.h"



PointLight::PointLight(Desc * _desc)
{
	m_color = _desc->color;
	m_intensity = _desc->intensity;
	m_radius = _desc->radius;

	m_lightMode = LIGHT_MODE_DIRECTIONAL;
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

void PointLight::Release()
{
	m_lightManager->DeletePointLight(this);
}
