#pragma warning(disable:4819)

#include "stdafx.h"
#include "MainGame.h"
#include "Core.h"
#include "TitleScene.h"
#include "StageScene.h"
#include "NextSceneLoad.h"
#include "GarageScene.h"
#include "StageSelectScene.h"
#include "PhantomScene.h"
#include "Stage2Scene.h"
#include "UILabScene.h"
#include "HeeTestScene.h"
#include "NalmakScene.h"

TimeManager* g_time;
// rendering pipeline
// local -> world -> view -> backface -> light -> projection -> cliping -> viewport -> rasterize


MainGame::MainGame()
{

}


MainGame::~MainGame()
{
	Core::DestroyInstance();
}

int MainGame::Run()
{
	m_engine = Core::GetInstance();
	g_time = TimeManager::GetInstance();

	ApplicationSetting();

	ReadyResource();

	ReadyPrototype();

	SystemSetting();

	InstantiateDefault();


	MSG msg;
	try
	{
		while (true)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			m_engine->Run();
		}

		return (int)msg.wParam;
	}
	catch (Exception& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		assert(0);
		return 0;
	}
}


void MainGame::ApplicationSetting()
{
	Core::Desc core;
	core.OBJECT_TAG_COUNT = OBJECT_TAG::OBJECT_TAG_MAX;
	core.COLLISION_LAYER_COUNT = COLLISION_LAYER_MAX;
	core.wincx = WINCX;
	core.wincy = WINCY;
	core.windowMode = true;

	// all resource load in resource directory
	core.resourceDirectoryPath;
	core.CANVAS_GROUP_COUNT = CANVAS_GROUP_MAX;

	m_engine->Initialize(g_hWnd, &core);
}

void MainGame::SystemSetting()
{
	auto editor = INSTANTIATE()->AddComponent<EditController>();
	editor->SetDontDestroy(true);
	//m_engine->ActivateCollisionByLayer(COLLISION_LAYER_DEFAULT, COLLISION_LAYER_DEFAULT);
	m_engine->ActivateCollisionByLayer(COLLISION_LAYER_BULLET_PLAYER, COLLISION_LAYER_ENEMY);
	m_engine->ActivateCollisionByLayer(COLLISION_LAYER_BULLET_ENEMY, COLLISION_LAYER_PLAYER);

	m_engine->AddScene(L"title", Scene::Instantiate<TitleScene>());
	m_engine->AddScene(L"garage", Scene::Instantiate<GarageScene>());
	m_engine->AddScene(L"stageSelect", Scene::Instantiate<StageSelectScene>());
	m_engine->AddScene(L"stage", Scene::Instantiate<StageScene>());
	m_engine->AddScene(L"stage2", Scene::Instantiate<Stage2Scene>());
	m_engine->AddScene(L"UILab", Scene::Instantiate<UILabScene>());
	m_engine->AddScene(L"phantom", Scene::Instantiate<PhantomScene>());


	m_engine->AddScene(L"Hee", Scene::Instantiate<HeeTestScene>());
	m_engine->AddScene(L"nalmak", Scene::Instantiate<NalmakScene>());


	m_engine->SetStartScene(L"garage");

}

void MainGame::ReadyResource()
{




}

void MainGame::ReadyPrototype()
{




}

void MainGame::InstantiateDefault()
{


}
