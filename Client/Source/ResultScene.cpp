#include "stdafx.h"
#include "..\Include\ResultScene.h"
#include "UIWindowFactory.h"


ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>();

	UIWindowFactory::ResultSceneTest();
}
