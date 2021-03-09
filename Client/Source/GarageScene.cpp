#include "stdafx.h"
#include "..\Include\GarageScene.h"

#include "core.h"
#include "SceneChanger.h"
#include "PlayerInfoManager.h"

#include "UIWindowFactory.h"
#include "UILabScene.h"
#include "StageManager.h"
#include "ItemManager.h"


#include "GarageSceneCameraAutoRotate.h"
#include "GarageSceneCameraIntro.h"
#include "GarageSceneCameraZoomIn.h"
#include "GarageSceneCameraMouseInput.h"
#include "GarageSceneCameraInfo.h"
#include "CustomDebuger.h"
#include "PlayerShooter.h"
#include "EnemyManager.h"

GarageScene::GarageScene()
{
}


GarageScene::~GarageScene()
{
}

void GarageScene::Initialize()
{
	DirectionalLight::Desc  directional;
	directional.diffuseIntensity = 0.5f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&directional)->SetRotation(50, 0, 0);
	//StageManager::GetInstance();

	ItemManager::GetInstance();



	{
		PointLight::Desc point;
		point.radius = 8.f;
		point.color = Vector3(1, 0.7f, 0.6f);
		point.diffuseIntensity = 4.f;
		INSTANTIATE()->AddComponent<PointLight>(&point)->SetPosition(3, 1, 4);

	}
	{
		PointLight::Desc point;
		point.radius = 12.f;
		point.color = Vector3(0.5f, 0.5, 0.7f);
		point.diffuseIntensity = 2.f;
		INSTANTIATE()->AddComponent<PointLight>(&point)->SetPosition(2,-1,-4);
	}
	{
		PointLight::Desc point;
		point.radius = 10.f;
		point.color = Vector3(0.9f, 0.9f, 0.7f);
		point.diffuseIntensity = 2.5f;
		INSTANTIATE()->AddComponent<PointLight>(&point)->SetPosition(-3, 2, 4);
	}
	INSTANTIATE()->AddComponent<Grid>()->SetPosition(0,0,-5.f);

	INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);


	auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>()
		->AddComponent<StateControl>()->AddComponent<GarageSceneCameraInfo>()->AddComponent<CustomDebuger>();
	mainCam->GetComponent<StateControl>()->AddState<GarageSceneCameraAutoRotate>(L"autoRotate");
	mainCam->GetComponent<StateControl>()->AddState<GarageSceneCameraIntro>(L"intro");
	mainCam->GetComponent<StateControl>()->AddState<GarageSceneCameraZoomIn>(L"zoomIn");
	mainCam->GetComponent<StateControl>()->AddState<GarageSceneCameraMouseInput>(L"mouseInput");
	mainCam->GetComponent<StateControl>()->InitState(L"intro");

	GameObject* player;
	{
		MeshRenderer::Desc render;
		render.mtrlName = L"f15";
		render.meshName = L"f15";
		player = INSTANTIATE(OBJECT_TAG_PLAYER, L"player")->AddComponent<MeshRenderer>(&render);
		player->SetScale(0.1f, 0.1f, 0.1f);
	}

	{
		VIBufferRenderer::Desc render;
		render.mtrlName = L"Garage_BG";
		render.meshName = L"screenQuad";
		auto obj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"background")->AddComponent<VIBufferRenderer>(&render);
		obj->GetComponent<VIBufferRenderer>()->SetFrustumCulling(false);
	}


	player->AddComponent<UIInteractor>();
	UIWindowFactory::GarageMainWindow(player);
}
