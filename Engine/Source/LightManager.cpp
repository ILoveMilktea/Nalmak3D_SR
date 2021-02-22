#include "LightManager.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "DirectionalLight.h"
IMPLEMENT_SINGLETON(LightManager)

LightManager::LightManager()
{
}


LightManager::~LightManager()
{
}

void LightManager::Initialize()
{
	m_skyBoxVIBuffer = ResourceManager::GetInstance()->GetResource<VIBuffer>(L"skyBox");
	m_skyBoxMtrl = ResourceManager::GetInstance()->GetResource<Material>(L"skyBox");
}

void LightManager::SetSkyBox(const wstring & _skyBoxName)
{
	m_skyBoxMtrl->SetTexture("g_skyBox", _skyBoxName);
}

void LightManager::SetDirectionalLightInfo(DirectionalLight * _light)
{
	if (m_directionalLigth)
		assert(L"Already Directional light is exist!" && 0);

	m_directionalLigth = _light;
}

void LightManager::DeleteDirectionalLight()
{
	m_directionalLigth = nullptr;
}

void LightManager::DeletePointLight(PointLight * _light)
{
	for (auto iter = m_pointLights.begin(); iter != m_pointLights.end(); ++iter)
	{
		if ((*iter) == _light)
		{
			m_pointLights.erase(iter);
			return;
		}
	}
}

void LightManager::AddPointLight(PointLight * _light)
{
	m_pointLights.emplace_back(_light);
}

bool LightManager::GetDirectionalLightInfo(DirectionalLightInfo& _info)
{
	if (m_directionalLigth)
	{
		_info = m_directionalLigth->GetDirectionalLightInfo();
		return true;
	}
	else
		return false;
}

VIBuffer * LightManager::GetSkyboxVIBuffer()
{
	return m_skyBoxVIBuffer;
}

Material * LightManager::GetSkyboxMaterial()
{
	return m_skyBoxMtrl;
}

