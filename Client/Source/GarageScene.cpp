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

GarageScene::GarageScene()
{
}


GarageScene::~GarageScene()
{
}

void GarageScene::Initialize()
{
	//StageManager::GetInstance();

	ItemManager::GetInstance(); 

	// singlemanger instance
	

	//
	//grid setting
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
		VIBufferRenderer::Desc render;
		render.mtrlName = L"default"; 
		render.meshName = L"flight";
		player = INSTANTIATE(OBJECT_TAG_PLAYER, L"player")->AddComponent<VIBufferRenderer>(&render);
		player->SetScale(0.1f, 0.1f, 0.1f);
	}

	
	/*{
		RevolvesToTarget::Desc revolvesDesc;
		revolvesDesc.targetParent = player;
		revolvesDesc.roationSpeed = 1.f;
		auto revolvesTarget = INSTANTIATE()->AddComponent<RevolvesToTarget>(&revolvesDesc);
	}*/
	
	// test button ----> UILab
	{
		//auto mainEquipWepon = UIFactory::CreateButton(
		//	EventHandler([]() {
		//	ItemDesc * ItemDescInfo = PlayerKitSelector::GetInstance()->FindSlotItme(L"Weapon", ITEMTYPE::ITEMTYPE_CANNON);
		//	PlayerInfoManager::GetInstance()->EquipWepon(PARTS_NUM::FIRST_PARTS , ItemDescInfo);
	 // �ֹ���
		

		//}));

		//mainEquipWepon->SetPosition(1600.f, 500.f, 0.f);



		//auto offTheFieldButton = UIFactory::CreateButton(
		//	EventHandler([]() {
		//	Core::GetInstance()->LoadScene(L"phantom");
		//}));

		//offTheFieldButton->SetPosition(1600.f, 800.f, 0.f);
	}

	player->AddComponent<UIInteractor>();
	UIWindowFactory::GarageMainWindow(player);
}
