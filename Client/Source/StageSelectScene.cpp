#include "stdafx.h"

#include "..\Include\StageSelectScene.h"
#include "MoveBySpline.h"
#include "StageSelectCamera.h"
#include "StageSelectCamera_Idle.h"
#include "StageSelectCamera_Intro.h"
#include "StageSelectCamera_Stage1.h"
#include "StageSelectCamera_Stage2.h"
#include "ExplosionButton.h"
#include "verticalBillboard.h"
#include "MoveStageByMeshPicking.h"

//test


StageSelectScene::StageSelectScene()
{
}


StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::Initialize()
{
	DirectionalLight::Desc dir;
	dir.diffuseIntensity = 2.f;
	dir.ambientIntensity = 0.05f;

	INSTANTIATE()->AddComponent<DirectionalLight>(&dir)->SetRotation(50, 20, 0);

	{
		auto cam = INSTANTIATE()->AddComponent<Camera>()->AddComponent<StageSelectCamera>()->AddComponent<StateControl>();
		cam->GetComponent<StateControl>()->AddState<StageSelectCamera_Intro>(L"intro");
		cam->GetComponent<StateControl>()->AddState<StageSelectCamera_Idle>(L"idle");
		cam->GetComponent<StateControl>()->AddState<StageSelectCamera_Stage1>(L"stage1");
		cam->GetComponent<StateControl>()->AddState<StageSelectCamera_Stage2>(L"stage2");
		cam->GetComponent<StateControl>()->InitState(L"intro");
	}
	


	{
		VIBufferRenderer::Desc render;
		render.mtrlName = L"StageSelect_BG";
		render.meshName = L"quadNoneNormal";
		auto obj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"background")->AddComponent<VIBufferRenderer>(&render)->SetScale(2, 2, 1);
		obj->GetComponent<VIBufferRenderer>()->SetFrustumCulling(false);
	}

	{
		Terrain::Desc render;
		render.mtrlName = L"StageSelect_Floor";
		render.interval = 3.f;
		INSTANTIATE()->AddComponent<Terrain>(&render)->SetPosition(-150,0,0);
	}

	

	

	INSTANTIATE()->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);





}
