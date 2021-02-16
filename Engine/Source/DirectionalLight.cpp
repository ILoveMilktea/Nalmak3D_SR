#include "DirectionalLight.h"
#include "LightManager.h"
#include "Transform.h"

DirectionalLight::DirectionalLight(Desc * _desc)
{
	m_color = _desc->color;
	m_intensity = _desc->intensity;
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::Initialize()
{
	m_lightManager = LightManager::GetInstance();
	m_lightManager->SetDirectionalLightInfo(this);
}

void DirectionalLight::Update()
{
}

void DirectionalLight::Release()
{
	m_lightManager->DeleteDirectionalLight();
}

DirectionalLightInfo DirectionalLight::GetDirectionalLightInfo()
{
	return DirectionalLightInfo(-m_transform->GetForward(), m_color, m_intensity);
}


