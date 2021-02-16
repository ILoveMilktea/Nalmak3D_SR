#include "stdafx.h"
#include "TitleScene.h"
#include "NextSceneLoad.h"
#include "TestComponent.h"
#include "core.h"
#include "PlaneController.h"
#include "PlaneInfo.h"
#include "ClimbTerrain.h"
void TitleScene::Initialize()
{
	Core::GetInstance()->SetSkyBox(L"skyBox_default");

	INSTANTIATE()->AddComponent<Grid>();

	DirectionalLight::Desc light;
	light.intensity = 1.f;

	AutoRotate::Desc rot;
	rot.xAxisSpeed = 0.5f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(50, 20, 0)->AddComponent<AutoRotate>(&rot);
	
	{
		Camera::Desc cam;
		cam.renderMode = CAMERA_RENDERING_MODE_DEFERRED;
		auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>(&cam)->AddComponent<FreeMove>();
		mainCam->GetComponent<Camera>()->OffLayer(RENDER_LAYER_UI);
		mainCam->GetComponent<Camera>()->SetRenderTarget(0, L"mainRT_diffuse");
		mainCam->GetComponent<Camera>()->SetRenderTarget(1, L"mainRT_normal");
		mainCam->GetComponent<Camera>()->SetRenderTarget(2, L"mainRT_depthStencil");
		//mainCam->GetComponent<Camera>()->SetRenderTarget(3, L"mainRT_normal");

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
		renderer.mtrlName = L"mainRT_light";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 300, 0);
	}
	{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.mtrlName = L"mainRT_depthStencil";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 500, 0);
	}
	{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.mtrlName = L"mainRT_normal";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 700, 0);
	}
	/*{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.mtrlName = L"mainRT_motionNSpec";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 900, 0);
	}*/
	{
		MeshRenderer::Desc renderer;
		renderer.layer = RENDER_LAYER_UI;
		renderer.meshName = L"quadNoneNormal";
		renderer.mtrlName = L"lightPass";
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(WINCX, WINCY, 0);
	}

	{
	
	}

	INSTANTIATE(OBJECT_TAG_DEBUG,L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(-HALF_WINCX, HALF_WINCY, 0);

	

}
