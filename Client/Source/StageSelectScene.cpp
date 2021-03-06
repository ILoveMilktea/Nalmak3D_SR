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
	//dir.color = { 0.7f,0.8f,0.8f };

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
		//auto cam = INSTANTIATE()->AddComponent<Camera>()->AddComponent<FreeMove>();
	}


	/*cam->GetComponent<MoveBySpline>()
		->AddSplinePoint({ 0,0,0 })
		->AddSplinePoint({ 0,5,3 })
		->AddSplinePoint({ 2,6,30 })
		->AddSplinePoint({ 7,12,-40 })
		->AddSplinePoint({ -35,-6,20 })
		->AddSplinePoint({ 50,15,30 })
		->AddSplinePoint({ 70,30,50 });*/
	/*{
		MeshRenderer::Desc render;
		render.mtrlName = L"StageSelect_BG";
		render.meshName = L"quadNoneNormal";
		auto obj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"background")->AddComponent<MeshRenderer>(&render)->SetScale(2, 2, 1);
		obj->GetComponent<MeshRenderer>()->SetFrustumCulling(false);
	}*/
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

	/*{
		VIBufferRenderer::Desc render;
		render.meshName = L"box";
		render.mtrlName = L"standard";
		auto obj = INSTANTIATE()->AddComponent<VIBufferRenderer>(&render)->AddComponent<ExplosionButton>()->SetPosition(15,0.5f,15);
		obj->GetComponent<VIBufferRenderer>()->SetFrustumCulling(false);

	}*/


	/*{
		MeshRenderer::Desc render;
		render.meshName = L"planeTest";
		INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetPosition(0, 0, 5);
	}*/


	/*auto window1 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Diffuse", CANVAS_GROUP_G1);
	window1->SetPosition(100, 100, 0)->SetScale(200, 200, 0);
	auto window2 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Normal", CANVAS_GROUP_G1);
	window2->SetPosition(100, 300, 0)->SetScale(200, 200, 0);
	auto window3 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Depth", CANVAS_GROUP_G1);
	window3->SetPosition(100, 500, 0)->SetScale(200, 200, 0);
	auto window4 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Light", CANVAS_GROUP_G1);
	window4->SetPosition(100, 700, 0)->SetScale(200, 200, 0);
	auto window5 = UIFactory::CreateRenderTargetWindow(L"GBuffer_CookTorrance", CANVAS_GROUP_G1);
	window5->SetPosition(100, 900, 0)->SetScale(200, 200, 0);*/

	INSTANTIATE()->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);





}
