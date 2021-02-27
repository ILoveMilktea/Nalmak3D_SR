#include "stdafx.h"
#include "..\Include\PhantomScene.h"
#include "NextSceneLoad.h"
#include "core.h"

#include "PlayerInfoManager.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"

#include "FixToTarget.h"
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
	srand((unsigned int)time(NULL));

	auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>();

	StageManager::GetInstance();



	Core::GetInstance()->SetSkyBox(L"skybox_gradation");
	//MeshRenderer::Desc ground;
	//ground.mtrlName = L"ground";
	//ground.meshName = L"ground";
	//auto groundObj = INSTANTIATE()->AddComponent<MeshRenderer>(&ground)->SetRotation(90, 0, 0);
	//groundObj->GetComponent<MeshRenderer>()->SetFrustumCulling(false);

	DirectionalLight::Desc light;
	light.diffuseIntensity = 1.f;
	light.ambientIntensity = 0.2f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(60, 30, 0);

	
	
	
	//GameObject* player;
	
	

	//INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	//INSTANTIATE()->AddComponent<Grid>();

	//{
	//	MeshRenderer::Desc render;
	//	render.mtrlName = L"default"; // 210223화 12:50 전근희 제대로 안나와서 설정 바꿨음
	//	render.meshName = L"flight";

	//	player = INSTANTIATE(OBJECT_TAG_PLAYER,L"player")->AddComponent<MeshRenderer>(&render)->AddComponent<StateControl>()->AddComponent<PlayerInfoManager>()->AddComponent<DrawGizmo>()->AddComponent<MouseOption>();;
	//	/*근희 추가*/
	//	player->AddComponent<PlayerToTopView>();

	//	player->GetComponent<StateControl>()->AddState<PlayerIdle>(L"playerIdle")->AddState<PlayerMove>(L"playerMove");
	//	player->GetComponent<StateControl>()->InitState(L"playerIdle");
	//	player->SetScale(0.1f, 0.1f, 0.1f);
	//		
	//}

	//{
	//	SmoothFollow::Desc smoothFollowDesc;
	//	smoothFollowDesc.toTarget = player;
	//	auto smoothFollow = INSTANTIATE(0, L"SmoothFollow")->AddComponent<SmoothFollow>(&smoothFollowDesc);
	//}

	////GameObject* Enemy = nullptr;
	////Enemy = INSTANTIATE(OBJECT_TAG_ENEMY, L"enemy");

	////MeshRenderer::Desc Enemy_render;
	////Enemy_render.mtrlName = L"steel";
	////Enemy_render.meshName = L"flight";
	////Enemy->AddComponent<MeshRenderer>(&Enemy_render);
	//
	//EnemyManager::GetInstance();



	

	
}
