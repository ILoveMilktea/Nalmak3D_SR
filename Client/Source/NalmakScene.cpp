#include "stdafx.h"
#include "..\Include\NalmakScene.h"
#include "PrintInfo.h"

NalmakScene::NalmakScene()
{
}

NalmakScene::~NalmakScene()
{
}

void NalmakScene::Initialize()
{
	INSTANTIATE()->AddComponent<Grid>();

	//Core::GetInstance()->SetSkyBox(L"skyBox_default");
	AutoRotate::Desc rot;
	rot.xAxisSpeed = 1;
	DirectionalLight::Desc light;
	light.diffuseIntensity = 1.f;
	light.ambientIntensity = 0.2f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(60, 30, 0)->AddComponent<AutoRotate>(&rot);
	{
		FreeMove::Desc free;
		auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>()->AddComponent<FreeMove>(&free)->AddComponent<PrintInfo>()->SetPosition(0, 0, -5);
	}

	{
		for (int i = 0; i < 200; ++i)
		{
			MeshRenderer::Desc mesh;
			mesh.meshName = L"sphere";
			mesh.mtrlName = L"standard";
			INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)->SetScale(Vector3(1, 1, 1) * Nalmak_Math::Rand(1.f, 3.f))->SetPosition(Nalmak_Math::Rand(-60.f, 60.f), Nalmak_Math::Rand(1.f, 20.f), Nalmak_Math::Rand(-60.f, 60.f));
		}

		{
			PointLight::Desc point;
			point.diffuseIntensity = 1.f;
			point.ambientIntensity = 0.1f;

		/*	for (int i = 0; i < 100; ++i)
			{
				point.color = Vector3(Nalmak_Math::Rand(0.f, 1.f), Nalmak_Math::Rand(0.f, 1.f), Nalmak_Math::Rand(0.f, 1.f));
				point.diffuseIntensity = Nalmak_Math::Rand(1.f, 7.f);
				point.radius = Nalmak_Math::Rand(30.f, 60.f);
				INSTANTIATE()->AddComponent<PointLight>(&point)->SetPosition(Nalmak_Math::Rand(-60.f, 60.f), Nalmak_Math::Rand(1.f, 20.f), Nalmak_Math::Rand(-60.f, 60.f));
			}*/
		}
		MeshRenderer::Desc mesh;
		mesh.mtrlName = L"transTest";
		mesh.meshName = L"box";
		INSTANTIATE()->AddComponent<MeshRenderer>(&mesh);
	}

	{
		SingleImage::Desc single;
		auto obj = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>();
		obj->GetComponent<SingleImage>()->SetTexture(ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Diffuse")->GetTexture());
		obj->SetPosition(100, 100, 0)->SetScale(200, 200, 0);
	}
	{
		SingleImage::Desc single;
		auto obj = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>();
		obj->GetComponent<SingleImage>()->SetTexture(ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Normal")->GetTexture());
		obj->SetPosition(100, 300, 0)->SetScale(200, 200, 0);
	}
	{
		SingleImage::Desc single;
		auto obj = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>();
		obj->GetComponent<SingleImage>()->SetTexture(ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Depth")->GetTexture());
		obj->SetPosition(100, 500, 0)->SetScale(200, 200, 0);
	}
	{
		SingleImage::Desc single;
		auto obj = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>();
		obj->GetComponent<SingleImage>()->SetTexture(ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Light")->GetTexture());
		obj->SetPosition(100, 700, 0)->SetScale(200, 200, 0);
	}
	

	INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
}
