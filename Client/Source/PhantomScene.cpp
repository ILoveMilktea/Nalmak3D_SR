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
PhantomScene::PhantomScene()
{
}


PhantomScene::~PhantomScene()
{
}

void PhantomScene::Initialize()
{
	GameObject* player;
	{
		auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>();
	}

	INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	INSTANTIATE()->AddComponent<Grid>();

	{
		MeshRenderer::Desc render;
		render.mtrlName = L"standard";
		render.meshName = L"flight";

		player = INSTANTIATE(OBJECT_TAG_PLAYER,L"player")->AddComponent<MeshRenderer>(&render)->AddComponent<StateControl>()->AddComponent<PlayerInfoManager>()->AddComponent<DrawGizmo>()->AddComponent<MouseOption>();;
		player->GetComponent<StateControl>()->AddState<PlayerIdle>(L"playerIdle")->AddState<PlayerMove>(L"playerMove");
		player->GetComponent<StateControl>()->InitState(L"playerIdle");
		player->SetScale(0.1f, 0.1f, 0.1f);
	}

	{
		SmoothFollow::Desc smoothFollowDesc;
		smoothFollowDesc.toTarget = player;
		auto smoothFollow = INSTANTIATE()->AddComponent<SmoothFollow>(&smoothFollowDesc);
	}


	//GameObject* Enemy = nullptr;
	//Enemy = INSTANTIATE(OBJECT_TAG_ENEMY, L"enemy");

	//MeshRenderer::Desc Enemy_render;
	//Enemy_render.mtrlName = L"steel";
	//Enemy_render.meshName = L"flight";
	//Enemy->AddComponent<MeshRenderer>(&Enemy_render);
	
	EnemyManager::GetInstance();



	

	
	
}
