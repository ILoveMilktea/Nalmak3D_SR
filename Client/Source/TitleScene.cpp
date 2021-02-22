#include "stdafx.h"
#include "TitleScene.h"
#include "NextSceneLoad.h"
#include "TestComponent.h"
#include "core.h"
#include "PlaneController.h"
#include "PlaneInfo.h"
#include "ClimbTerrain.h"
#include "PrintInfo.h"
void TitleScene::Initialize()
{
	Core::GetInstance()->SetSkyBox(L"skyBox_default");

	INSTANTIATE()->AddComponent<Grid>();

	DirectionalLight::Desc light;
	light.intensity = 1.f;
	AutoRotate::Desc rot;
	rot.xAxisSpeed = 0.5f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(60, 20, 0);// ->AddComponent<AutoRotate>(&rot);
	
	{
		Camera::Desc cam;
		cam.renderMode = CAMERA_RENDERING_MODE_DEFERRED;
		FreeMove::Desc free;
		free.wheelMoveSpeed = 2.f;
		auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>(&cam)->AddComponent<FreeMove>(&free)->AddComponent<PrintInfo>();
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
		point.diffuseIntensity = 1.f;
		point.ambientIntensity = 0.1f;
		MeshRenderer::Desc mesh;
		mesh.meshName = L"sphere";

		for (int i = 0; i < 100; ++i)
		{
			point.color = Vector3(Nalmak_Math::Rand(0.f, 1.f), Nalmak_Math::Rand(0.f, 1.f), Nalmak_Math::Rand(0.f, 1.f));
			point.diffuseIntensity = Nalmak_Math::Rand(1.f,7.f);
			point.radius = Nalmak_Math::Rand(30.f, 60.f);

			INSTANTIATE()->AddComponent<PointLight>(&point)->SetPosition(Nalmak_Math::Rand(-60.f, 60.f), Nalmak_Math::Rand(1.f, 20.f), Nalmak_Math::Rand(-60.f, 60.f));
		}
	}
	{
		for (int i = 0; i < 200; ++i)
		{
			MeshRenderer::Desc mesh;
			mesh.meshName = L"sphere";
			mesh.mtrlName = L"standard";
			INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)->SetScale(Vector3(1,1,1) * Nalmak_Math::Rand(1.f, 3.f))->SetPosition(Nalmak_Math::Rand(-60.f, 60.f), Nalmak_Math::Rand(1.f, 20.f), Nalmak_Math::Rand(-60.f, 60.f));
		}
		
	}
	MeshRenderer::Desc mesh;
	mesh.meshName = L"teapot";
	mesh.mtrlName = L"standard";
	INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)->SetPosition(0, 0, 2);




	{
		MeshRenderer::Desc render;
		render.mtrlName = L"standard";
		render.meshName = L"plane";
		INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetPosition(0, 0, -1)->SetScale(100, 100, 100);
	}


	

	INSTANTIATE(OBJECT_TAG_DEBUG,L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(-HALF_WINCX, HALF_WINCY, 0);

	

}
