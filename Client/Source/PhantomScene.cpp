#include "stdafx.h"
#include "..\Include\PhantomScene.h"
#include "NextSceneLoad.h"
#include "core.h"

#include "PlayerInfoManager.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"

#include "MouseOption.h"
#include "SmoothFollow.h"

#include "EnemyManager.h"

#include "StageManager.h"

#include "UIWindowFactory.h"

PhantomScene::PhantomScene()
{

}


PhantomScene::~PhantomScene()
{
}

void PhantomScene::Initialize()
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


	srand((unsigned int)time(NULL));

	auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>();

	StageManager::GetInstance();





}
