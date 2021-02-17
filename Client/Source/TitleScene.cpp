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
		FreeMove::Desc free;
		free.wheelMoveSpeed = 2.f;
		auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>(&cam)->AddComponent<FreeMove>(&free);
		//mainCam->GetComponent<Camera>()->OffLayer(RENDER_LAYER_UI);
		mainCam->SetPosition(0, 4, -6);
		mainCam->SetRotation(30, 0, 0);
		mainCam->SetDontDestroy(true);
	}
	/*{
		Camera::Desc cam;
		cam.renderMode = CAMERA_RENDERING_MODE_DEFERRED;
		auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>(&cam)->AddComponent<FreeMove>();
		mainCam->GetComponent<Camera>()->AllOffLayer();
		mainCam->GetComponent<Camera>()->OnLayer(RENDER_LAYER_UI);

		mainCam->SetPosition(0, 0, -6);
		mainCam->SetDontDestroy(true);
	}*/
	{
		PointLight::Desc point;
		point.radius = 5;
			INSTANTIATE()->AddComponent<PointLight>(&point);//->SetPosition(Nalmak_Math::RandDirection() * Nalmak_Math::Rand(-30.f, 30.f));;

	
	}
	{
		MeshRenderer::Desc mesh;
		mesh.meshName = L"sphere";
		mesh.mtrlName = L"standard";
		INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)->SetScale(3, 3, 3)->SetPosition(3,0,0);
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
	/*{
		MeshRenderer::Desc renderer;
		renderer.mtrlName = L"GBuffer_diffuse";
		renderer.layer = RENDER_LAYER_UI;
		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 100, 0);
	}
	{
		MeshRenderer::Desc renderer;
		renderer.mtrlName = L"GBuffer_light";
		renderer.layer = RENDER_LAYER_UI;

		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 300, 0);
	}
	{
		MeshRenderer::Desc renderer;
		renderer.mtrlName = L"GBuffer_depthStencil";
		renderer.layer = RENDER_LAYER_UI;

		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 500, 0);
	}
	{
		MeshRenderer::Desc renderer;
		renderer.mtrlName = L"GBuffer_normal";
		renderer.layer = RENDER_LAYER_UI;

		INSTANTIATE()->AddComponent<MeshRenderer>(&renderer)->SetScale(200, 200, 0)->SetPosition(-HALF_WINCX + 100, HALF_WINCY - 700, 0);
	}*/


	

	INSTANTIATE(OBJECT_TAG_DEBUG,L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(-HALF_WINCX, HALF_WINCY, 0);

	

}
