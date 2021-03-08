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
	INSTANTIATE()->AddComponent<DirectionalLight>()->SetRotation(90, 0, 0);
	//StageManager::GetInstance();

	ItemManager::GetInstance();


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


	auto window1 = UIFactory::CreateRenderTargetWindow(L"Garage_SkillPreview", CANVAS_GROUP_G1);
	window1->SetPosition(500, 500, 0)->SetScale(500, 500, 0);

	player->AddComponent<UIInteractor>();
	UIWindowFactory::GarageMainWindow(player);
}
