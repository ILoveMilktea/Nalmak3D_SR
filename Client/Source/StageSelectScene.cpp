#include "stdafx.h"
#include "..\Include\StageSelectScene.h"
#include "MoveBySpline.h"

StageSelectScene::StageSelectScene()
{
}


StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::Initialize()
{
	INSTANTIATE()->AddComponent<DirectionalLight>();
	auto cam = INSTANTIATE()->AddComponent<Camera>()->AddComponent<FreeMove>();// ->AddComponent<MoveBySpline>()->SetPosition(0, 0, 0);
	/*cam->GetComponent<MoveBySpline>()
		->AddSplinePoint({ 0,0,0 })
		->AddSplinePoint({ 0,5,3 })
		->AddSplinePoint({ 2,6,30 })
		->AddSplinePoint({ 7,12,-40 })
		->AddSplinePoint({ -35,-6,20 })
		->AddSplinePoint({ 50,15,30 })
		->AddSplinePoint({ 70,30,50 });*/
	{
		MeshRenderer::Desc render;
		render.mtrlName = L"StageSelect_BG";
		render.meshName = L"quadNoneNormal";
		auto obj = INSTANTIATE(OBJECT_TAG_DEFAULT, L"background")->AddComponent<MeshRenderer>(&render)->SetScale(2, 2, 1);
		obj->GetComponent<MeshRenderer>()->SetFrustumCulling(false);
	}

	{
		Terrain::Desc render;
		render.mtrlName = L"StageSelect_Floor";
		render.interval = 3.f;
		INSTANTIATE()->AddComponent<Terrain>(&render);
	}
	INSTANTIATE()->AddComponent<SystemInfo>()->SetPosition(50, 50,0);



	ParticleRenderer::Desc particle;
	particle.particleDataName = L"fire";
	INSTANTIATE()->AddComponent<ParticleRenderer>(&particle);
}
