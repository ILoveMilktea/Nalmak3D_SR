#include "LightManager.h"
#include "GameObject.h"
#include "MeshRenderer.h"
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
