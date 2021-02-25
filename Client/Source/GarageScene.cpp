#include "stdafx.h"
#include "..\Include\GarageScene.h"
#include "RevolvesToTarget.h"
#include "core.h"
#include "SceneChanger.h"
#include "PlayerKitSelector.h"
GarageScene::GarageScene()
{
}


GarageScene::~GarageScene()
{
}

void GarageScene::Initialize()
{

//	 grid setting

	INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	
	auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>()->SetPosition(0, 0, -5);;

	GameObject* player;
	{
		MeshRenderer::Desc render;
		render.mtrlName = L"default"; 
		render.meshName = L"flight";
		player = INSTANTIATE(OBJECT_TAG_PLAYER, L"player")->AddComponent<MeshRenderer>(&render);
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
	{
		auto kitmanager = INSTANTIATE()->AddComponent<PlayerKitSelector>();
		//PlayerKitSelector::GetInstance()

	}

	{
		auto offTheFieldButton = UIFactory::CreateButton(
			EventHandler([]() {
			Core::GetInstance()->LoadScene(L"phantom");
		}));

		offTheFieldButton->SetPosition(1600.f, 800.f, 0.f);
	}
}
