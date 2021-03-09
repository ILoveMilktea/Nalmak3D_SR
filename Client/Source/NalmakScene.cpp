#include "stdafx.h"
#include "..\Include\NalmakScene.h"
#include "PrintInfo.h"
#include "SceneChanger.h"
#include "PlayerShooter.h"
#include "PlayerSkillActor.h"
#include "ItemManager.h"
#include"PlayerInfoManager.h"
#include "ScaleDampingDeffender.h"
#include "UIFactory.h"

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


	ItemManager::GetInstance()->BuyItem(L"Weapon", L"Emp");
	PlayerInfoManager::GetInstance()->EquipItem(PARTS_NUM::FIRST_PARTS, L"Weapon", L"Emp");

	{
		/*MeshRenderer::Desc render;
		render.meshName = L"f15";
		render.mtrlName = L"f15";

		plane = INSTANTIATE(OBJECT_TAG_PLAYER)->AddComponent<MeshRenderer>(&render)->SetPosition(0, 0, 0)->SetScale(0.2f, 0.2f, 0.2f);
		plane->GetComponent<MeshRenderer>()->SetFrustumCulling(false);
		plane->AddComponent<PlayerShooter>();
		plane->AddComponent<PlayerSkillActor>();*/
	}

	PlayerInfoManager::GetInstance()->GetPlayer();

	DirectionalLight::Desc light;
	light.diffuseIntensity = 0.6f;
	light.ambientIntensity = 0.02f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(60, 180, 0);


	{
		FreeMove::Desc free;
		INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>()
			->AddComponent<PrintInfo>()
			->AddComponent<FreeMove>()
			->SetPosition(0, 10, 15)
			->SetRotation(30, 50, 0);
	}





	auto window1 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Diffuse", CANVAS_GROUP_G1);
	window1->SetPosition(100, 100, 0)->SetScale(200, 200, 0);
	auto window2 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Normal", CANVAS_GROUP_G1);
	window2->SetPosition(100, 300, 0)->SetScale(200, 200, 0);
	auto window3 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Depth", CANVAS_GROUP_G1);
	window3->SetPosition(100, 500, 0)->SetScale(200, 200, 0);
	auto window4 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Light", CANVAS_GROUP_G1);
	window4->SetPosition(100, 700, 0)->SetScale(200, 200, 0);
	auto window5 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Distortion", CANVAS_GROUP_G1);
	window5->SetPosition(100, 900, 0)->SetScale(200, 200, 0);
	auto window6 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Debug", CANVAS_GROUP_G1);
	window6->SetPosition(300, 100, 0)->SetScale(200, 200, 0);
	auto window7 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Emission", CANVAS_GROUP_G1);
	window7->SetPosition(300, 300, 0)->SetScale(200, 200, 0);
	auto window8 = UIFactory::CreateRenderTargetWindow(L"Emisson_HorizontalBlur", CANVAS_GROUP_G1);
	window8->SetPosition(300, 500, 0)->SetScale(200, 200, 0);
	auto window9 = UIFactory::CreateRenderTargetWindow(L"Emisson_FinalBlur", CANVAS_GROUP_G1);
	window9->SetPosition(300, 700, 0)->SetScale(200, 200, 0);

	INSTANTIATE()->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	/*{
		VIBufferRenderer::Desc vibuffer;
		vibuffer.meshName = L"quadNoneNormal";	
		vibuffer.mtrlName = L"fx_20mmCannon";
		auto temp = INSTANTIATE()->AddComponent<VIBufferRenderer>(&vibuffer);
		temp->GetComponent<VIBufferRenderer>()->SetFrustumCulling(false);
	}*/

	{
		ParticleRenderer::Desc	distortion;
		distortion.particleDataName = L"player_zet_distortion";
		INSTANTIATE()->AddComponent<ParticleRenderer>(&distortion)->SetPosition(0.15f, 0.1f, -0.7f);
	}
	{
		ParticleRenderer::Desc	distortion;
		distortion.particleDataName = L"player_zet_distortion";
		INSTANTIATE()->AddComponent<ParticleRenderer>(&distortion)->SetPosition(-0.15f, 0.1f, -0.7f);
	}

	{
		VIBufferRenderer::Desc vibuffer;
		vibuffer.meshName = L"screenQuad";
		vibuffer.mtrlName = L"particleDistortion";
		INSTANTIATE()->AddComponent<VIBufferRenderer>(&vibuffer);
	}
	

	{
		VIBufferRenderer::Desc ground;
		ground.mtrlName = L"ground";
		ground.meshName = L"ground";
		auto groundObj = INSTANTIATE()->AddComponent<VIBufferRenderer>(&ground)->SetRotation(90, 0, 0);
		groundObj->GetComponent<VIBufferRenderer>()->SetFrustumCulling(false);
	}

	{
		ScaleDampingDeffender::Desc scaleDamping;
		scaleDamping.dampingSpeed = 3.f;
		scaleDamping.maximumScale = 15.0f;
		scaleDamping.axisDir = Vector3(0.f, 1.f, 0.f);

		VIBufferRenderer::Desc shield;
		shield.meshName = L"sphere";
		shield.mtrlName = L"fx_shield";
		INSTANTIATE()->AddComponent<VIBufferRenderer>(&shield)->SetPosition(0, 0, 5)->AddComponent<ScaleDampingDeffender>(&scaleDamping)->AddComponent<SphereCollider>();
	}

}
