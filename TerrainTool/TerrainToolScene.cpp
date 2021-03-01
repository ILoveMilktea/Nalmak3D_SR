#include "stdafx.h"
#include "TerrainToolScene.h"
#include "TerrainTool.h"

TerrainToolScene::TerrainToolScene()
{
}


TerrainToolScene::~TerrainToolScene()
{
}

void TerrainToolScene::Initialize()
{
	auto cam = INSTANTIATE()->AddComponent<Camera>()->SetPosition(2, 1, -10.f)->AddComponent<FreeMove>();
	INSTANTIATE()->AddComponent<Grid>();
	INSTANTIATE()->AddComponent<DirectionalLight>()->SetRotation(50,20,0);

	SystemInfo::Desc system;
	system.fontSize = { 10,20 };
	INSTANTIATE()->AddComponent<SystemInfo>(&system)->SetPosition(50, 50, 0);

	TerrainTool::Desc terrain;
	terrain.interval = 1.f;
	terrain.mtrlName = L"debugCollider";
	INSTANTIATE()->AddComponent<TerrainTool>(&terrain);

	INSTANTIATE()->AddComponent<TerrainTool>(&terrain)->SetPosition(100,0,0);

}
