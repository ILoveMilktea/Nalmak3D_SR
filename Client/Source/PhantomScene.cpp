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
#include "PlayerToTopView.h"

#include "StageManager.h"
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


	//GameObject* player;
	
	

	//INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	//INSTANTIATE()->AddComponent<Grid>();

	//{
	//	MeshRenderer::Desc render;
	//	render.mtrlName = L"default"; // 210223ȭ 12:50 ������ ����� �ȳ��ͼ� ���� �ٲ���
	//	render.meshName = L"flight";

	//	player = INSTANTIATE(OBJECT_TAG_PLAYER,L"player")->AddComponent<MeshRenderer>(&render)->AddComponent<StateControl>()->AddComponent<PlayerInfoManager>()->AddComponent<DrawGizmo>()->AddComponent<MouseOption>();;
	//	/*���� �߰�*/
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
