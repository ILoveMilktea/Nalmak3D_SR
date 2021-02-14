#include "stdafx.h"
#include "..\Include\TitleScene.h"
#include "NextSceneLoad.h"
#include "TestComponent.h"
#include "core.h"
#include "PlaneController.h"
#include "PlaneInfo.h"
#include "ClimbTerrain.h"
void TitleScene::Initialize()
{
	INSTANTIATE()->AddComponent<Grid>();

	
	{
		auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>()->AddComponent<FreeMove>();
		mainCam->GetComponent<Camera>()->OffLayer(RENDER_LAYER_UI);
	/*	mainCam->GetComponent<Camera>()->SetRenderTarget(0, L"mainRenderTarget1");
		mainCam->GetComponent<Camera>()->SetRenderTarget(1, L"mainRenderTarget2");
		mainCam->GetComponent<Camera>()->SetRenderTarget(2, L"mainRenderTarget3");
		mainCam->GetComponent<Camera>()->SetRenderTarget(3, L"mainRenderTarget4");*/


		mainCam->SetPosition(0, 4, -6);
		mainCam->SetRotation(30, 0, 0);
	}
	
	{
		Camera::Desc cam;
		cam.mode = CAMERA_PROJECTION_MODE_ORTHOGRAPHIC;
		cam.width = WINCX;
		cam.height = WINCY;
		auto uiCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"uiCamera")->AddComponent<Camera>(&cam);
		uiCam->GetComponent<Camera>()->AllOffLayer();
		uiCam->GetComponent<Camera>()->OnLayer(RENDER_LAYER_UI);
		uiCam->SetPosition(0, 0, -10);
	}
	{
		Terrain::Desc terrain;
		terrain.interval = 1.f;
		terrain.mtrlName = L"debugCollider";
		terrain.brushPower = 1.f;
		terrain.brushRadius = 2.f;
		auto terrainObj = INSTANTIATE()->AddComponent<Terrain>(&terrain);

		MeshRenderer::Desc render;
		render.meshName = L"quad";
		render.mtrlName = L"default";
		Rigidbody::Desc rigid;
		rigid.isGravity = false;
		ClimbTerrain::Desc terrainDesc;
		terrainDesc.terrain = terrainObj->GetComponent<Terrain>();
	}
	{
		MeshRenderer::Desc render;
		render.mtrlName = L"default2";
		render.meshName = L"quad";
		INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetPosition(0, 0, 10)->SetScale(10, 10, 10);
	}
	/*{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.mtrlName = L"mainRenderTarget1";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 100, 0);
	}
	{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.mtrlName = L"mainRenderTarget2";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 300, 0);
	}
	{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.mtrlName = L"mainRenderTarget3";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 500, 0);
	}
	{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.mtrlName = L"mainRenderTarget4";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 700, 0);
	}*/

	INSTANTIATE(OBJECT_TAG_DEBUG,L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(-HALF_WINCX, HALF_WINCY, 0);

	

}
