#include "stdafx.h"
#include "..\Include\GarageScene.h"
#include "RevolvesToTarget.h"
#include "core.h"
#include "SceneChanger.h"
#include "PlayerKitSelector.h"
#include "PlayerInfoManager.h"

#include "UILabScene.h"
#include "StageManager.h"

GarageScene::GarageScene()
{
}


GarageScene::~GarageScene()
{
}

void GarageScene::Initialize()
{
	//StageManager::GetInstance();

//	 grid setting
	INSTANTIATE()->AddComponent<Grid>()->SetPosition(0,0,-5.f);

	INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	auto kitmgr = PlayerKitSelector::GetInstance();
	auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>()->SetPosition(0, 0, -5);;

	GameObject* player;
	{
		MeshRenderer::Desc render;
		render.mtrlName = L"default"; 
		render.meshName = L"flight";
		player = INSTANTIATE(OBJECT_TAG_PLAYER, L"player")->AddComponent<MeshRenderer>(&render)->AddComponent<PlayerInfoManager>();
		player->SetScale(0.1f, 0.1f, 0.1f);
	}
	 
	// 플레이어 주위를 뱅뱅도는
	{
		RevolvesToTarget::Desc revolvesDesc;
		revolvesDesc.targetParent = player;
		revolvesDesc.roationSpeed = 1.f;
		auto revolvesTarget = INSTANTIATE()->AddComponent<RevolvesToTarget>(&revolvesDesc);
	}
	{
		SceneChanger::Desc SceneChangerDescInfo;
		SceneChangerDescInfo.keyState = KEY_STATE_ENTER;
		SceneChangerDescInfo.sceneName = L"phantom";
		auto SceneSelect = INSTANTIATE()->AddComponent<SceneChanger>(&SceneChangerDescInfo);
	}
	
	 // 주무장
		auto mainEquipWepon = UIFactory::CreateButton(
			EventHandler([]() {
			PlayerInfoManager::GetInstance()->EquipWepon(PARTS_NUM::FIRST_PARTS , PlayerKitSelector::GetInstance()->FindSlotItme(L"Weapon", ITEMTYPE::ITEMTYPE_MISSILE));
		}));

		mainEquipWepon->SetPosition(1600.f, 500.f, 0.f);
	


	{
		// ----> UILab으로 이동

		//auto offTheFieldButton = UIFactory::CreateButton(
		//	EventHandler([]() {
		//	Core::GetInstance()->LoadScene(L"phantom");
		//}));

		//offTheFieldButton->SetPosition(1600.f, 800.f, 0.f);
	}

	UILabScene::GarageMainWindow();
}


