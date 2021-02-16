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

void LightManager::SetSkyBox(const wstring & _skyBoxName)
{
	if (!m_skyBox)
	{
		MeshRenderer::Desc renderer;
		renderer.mtrl = ResourceManager::GetInstance()->GetResource<Material>(L"skyBox");
		renderer.meshName = L"skyBox";
		m_skyBox = INSTANTIATE()->AddComponent<MeshRenderer>(&renderer);
		m_skyBox->SetDontDestroy(true);
	}
	m_skyBox->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture("g_skyBox", _skyBoxName);
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

