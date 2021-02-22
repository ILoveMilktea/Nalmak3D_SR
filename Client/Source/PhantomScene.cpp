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

	Core * core = Core::GetInstance();
	core->SetSkyBox(L"skyBox_default");
	INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(-HALF_WINCX, HALF_WINCY, 0);
	INSTANTIATE()->AddComponent<Grid>();
	{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.mtrlName = L"mainRT_diffuse";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(HALF_WINCX,  - 100, 0);
	}
	{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.mtrlName = L"mainRT_depth";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(HALF_WINCX,  - 300, 0);
	}
	{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.mtrlName = L"mainRT_normal";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(HALF_WINCX,  - 500, 0);
	}
	{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.meshName = L"quadNoneNormal";
		renderer.mtrlName = L"deferredLighting";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(WINCX, WINCY, 0);
	}

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
