#include "stdafx.h"
#include "..\Include\StageScene.h"
#include "Nalmak_Include.h"

#include "NextSceneLoad.h"


void StageScene::Initialize()
{
	auto cam = INSTANTIATE()->AddComponent<Camera>();
	cam->GetTransform()->position = Vector3(0, 0, -1.f);
	VIBufferRenderer::Desc render;




	auto obj1 = INSTANTIATE()->AddComponent<VIBufferRenderer>(&render);
	obj1->SetScale(Vector3(1, 1, 3));


	INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(0, 0, 0);
}
