#include "stdafx.h"
#include "..\Include\StageScene.h"
#include "Nalmak_Include.h"

#include "NextSceneLoad.h"
#include "StageManager.h"


void StageScene::Initialize()
{
	srand((unsigned int)time(NULL));

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

	StageManager::GetInstance();
}
