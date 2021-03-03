#include "stdafx.h"
#include "..\Include\NalmakScene.h"
#include "PrintInfo.h"
#include "SceneChanger.h"
#include "PlayerShooter.h"
#include "PlayerSkillActor.h"
#include "ItemManager.h"
#include"PlayerInfoManager.h"
NalmakScene::NalmakScene()
{
}

NalmakScene::~NalmakScene()
{
}

void NalmakScene::Initialize()
{
	GameObject* plane;


	Core::GetInstance()->SetSkyBox(L"SkyBox1");

	ItemManager::GetInstance()->BuyItem(L"Weapon", L"AimMissile");
	PlayerInfoManager::GetInstance()->EquipItem(PARTS_NUM::FIRST_PARTS, L"Weapon", L"AimMissile");


	{
		MeshRenderer::Desc render;
		render.meshName = L"f15";
		render.mtrlName = L"f15_base";

		plane = INSTANTIATE(OBJECT_TAG_PLAYER)->AddComponent<MeshRenderer>(&render)->SetPosition(0, 0, 0);
		plane->GetComponent<MeshRenderer>()->SetFrustumCulling(false);
		plane->GetComponent<MeshRenderer>()->AddMaterial(L"f15_glass");
		plane->GetComponent<MeshRenderer>()->AddMaterial(L"f15_base");
		plane->AddComponent<PlayerShooter>();
		plane->AddComponent<PlayerSkillActor>();

		

	}




	DirectionalLight::Desc light;
	light.diffuseIntensity = 0.9f;
	light.ambientIntensity = 0.02f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(60, 180, 0);
	{
		FreeMove::Desc free;
		INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>()->AddComponent<PrintInfo>()->AddComponent<FreeMove>()->SetPosition(0, 10, 15)->SetRotation(30, 180, 0);
	}

	{
		
		for (int i = -5; i < 5; ++i)
		{
			for (int j = -5; j < 5; ++j)
			{
				VIBufferRenderer::Desc mesh;
				mesh.meshName = L"sphere";
				mesh.mtrlName = L"standard";
				INSTANTIATE()->AddComponent<VIBufferRenderer>(&mesh)->SetScale(Vector3(1.f, 1.f, 1.f) * Nalmak_Math::Rand(1.f, 3.f))->SetPosition(i * 3.f, 0, j * 3.f);
			}
		}

		{
		/*	PointLight::Desc point;
			point.diffuseIntensity = Nalmak_Math::Rand(1.f, 5.f);
			point.ambientIntensity = 0.f;

			for (int i = 0; i < 100; ++i)
			{
				point.color = Vector3(Nalmak_Math::Rand(0.f, 1.f), Nalmak_Math::Rand(0.f, 1.f), Nalmak_Math::Rand(0.f, 1.f));
				point.diffuseIntensity = Nalmak_Math::Rand(1.f, 2.f);
				point.radius = Nalmak_Math::Rand(5.f, 20.f);
				INSTANTIATE()->AddComponent<PointLight>(&point)->SetPosition(Nalmak_Math::Rand(-15.f, 15.f), Nalmak_Math::Rand(-2.f, 2.f), Nalmak_Math::Rand(-15.f, 15.f));
			}*/
		}
	
			
		VIBufferRenderer::Desc mesh;
		mesh.mtrlName = L"transTest";
		mesh.meshName = L"box";
		INSTANTIATE()->AddComponent<VIBufferRenderer>(&mesh);
	}

	auto window1 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Diffuse", CANVAS_GROUP_G1);
	window1->SetPosition(100, 100, 0)->SetScale(200, 200, 0);
	auto window2 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Normal", CANVAS_GROUP_G1);
	window2->SetPosition(100, 300, 0)->SetScale(200, 200, 0);
	auto window3 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Depth", CANVAS_GROUP_G1);
	window3->SetPosition(100, 500, 0)->SetScale(200, 200, 0);
	auto window4 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Light", CANVAS_GROUP_G1);
	window4->SetPosition(100, 700, 0)->SetScale(200, 200, 0);

	INSTANTIATE()->AddComponent<SystemInfo>()->SetPosition(50, 50,0);

	{
		


			/*MeshRenderer::Desc render;
			render.meshName = L"f15";
			render.mtrlName = L"standardPlane";

			auto obj = INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetPosition(0, 6, -1);
			obj->GetComponent<MeshRenderer>()->SetFrustumCullinwwwwwwwwwwwwwwwwwaaaaaaaag(false);
			obj->GetComponent<MeshRenderer>()->AddMaterial(L"standardPlaneGlass");
			obj->GetComponent<MeshRenderer>()->AddMaterial(L"standardPlane");*/
	}
	{
		VIBufferRenderer::Desc ground;
		ground.mtrlName = L"ground";
		ground.meshName = L"ground";
		auto groundObj =  INSTANTIATE()->AddComponent<VIBufferRenderer>(&ground)->SetRotation(90, 0, 0);
		groundObj->GetComponent<VIBufferRenderer>()->SetFrustumCulling(false);
	}

	

}
