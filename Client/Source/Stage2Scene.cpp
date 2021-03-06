#include "stdafx.h"
#include "..\Include\Stage2Scene.h"
#include "StageManager.h"


Stage2Scene::Stage2Scene()
{
}


Stage2Scene::~Stage2Scene()
{
}

void Stage2Scene::Initialize()
{
	Core::GetInstance()->SetSkyBox(L"SkyBox1");

	DirectionalLight::Desc light;
	light.diffuseIntensity = 0.6f;
	light.ambientIntensity = 0.02f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(60, 180, 0);

	VIBufferRenderer::Desc ground;
	ground.mtrlName = L"ground";
	ground.meshName = L"ground";
	auto groundObj = INSTANTIATE()->AddComponent<VIBufferRenderer>(&ground)->SetRotation(90, 0, 0);
	groundObj->GetComponent<VIBufferRenderer>()->SetFrustumCulling(false);

	auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>();

	StageManager::GetInstance()->ToDog();
}
