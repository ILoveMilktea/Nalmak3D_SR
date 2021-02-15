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
	//asdfghjkl;
	
	{
		auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>()->AddComponent<FreeMove>();
		mainCam->GetComponent<Camera>()->OffLayer(RENDER_LAYER_UI);
		mainCam->GetComponent<Camera>()->SetRenderTarget(0, L"mainRT_diffuse");
		mainCam->GetComponent<Camera>()->SetRenderTarget(1, L"mainRT_depth");
		mainCam->GetComponent<Camera>()->SetRenderTarget(2, L"mainRT_normal");
		mainCam->SetPosition(0, 4, -6);
		mainCam->SetRotation(30, 0, 0);
		mainCam->SetDontDestroy(true);
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
		uiCam->SetDontDestroy(true);
	}

	
	{
		MeshRenderer::Desc render;
		render.mtrlName = L"standard";
		render.meshName = L"box";
		INSTANTIATE()->AddComponent<MeshRenderer>(&render);
	}
	{
		MeshRenderer::Desc render;
		render.mtrlName = L"standard";
		render.meshName = L"teapot";
		INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetPosition(0, 0, 10)->SetScale(1, 1, 1);
	}

	{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.mtrlName = L"mainRT_diffuse";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 100, 0);
	}
	{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.mtrlName = L"mainRT_depth";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 300, 0);
	}
	{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.mtrlName = L"mainRT_normal";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 500, 0);
	}
	{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.meshName = L"quadNoneNormal";
		renderer.mtrlName = L"deferredLighting";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(WINCX, WINCY, 0);
	}

	{
	
	}

	INSTANTIATE(OBJECT_TAG_DEBUG,L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(-HALF_WINCX, HALF_WINCY, 0);

	

}
