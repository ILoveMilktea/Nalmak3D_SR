#include "stdafx.h"
#include "..\Include\StageScene.h"
#include "Nalmak_Include.h"

#include "NextSceneLoad.h"
#include "StageManager.h"
#include "DogFight_Stage1.h"
#include "DogFightState.h"
#include "EvasionState.h"
#include "BossState.h"
#include "SmoothFollow.h"
#include "FieldCameraInfo.h"
#include "FieldCameraSmoothFollowState.h"
#include "FieldCameraStartState.h"
#include "FieldCameraNearEnemyState.h"
#include "UIFactory.h"

void StageScene::Initialize()
{
	srand((unsigned int)time(NULL));

	auto window1 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Diffuse", CANVAS_GROUP_G1);
	window1->SetPosition(100, 100, 0)->SetScale(200, 200, 0);
	auto window2 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Normal", CANVAS_GROUP_G1);
	window2->SetPosition(100, 300, 0)->SetScale(200, 200, 0);
	auto window3 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Depth", CANVAS_GROUP_G1);
	window3->SetPosition(100, 500, 0)->SetScale(200, 200, 0);
	auto window4 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Light", CANVAS_GROUP_G1);
	window4->SetPosition(100, 700, 0)->SetScale(200, 200, 0);
	auto window5 = UIFactory::CreateRenderTargetWindow(L"GBuffer_Debug", CANVAS_GROUP_G1);
	window5->SetPosition(100, 900, 0)->SetScale(200, 200, 0);

	Core::GetInstance()->SetSkyBox(L"SkyBox1");
	
	DirectionalLight::Desc light;
	light.diffuseIntensity = 0.6f;
	light.ambientIntensity = 0.02f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(60, 180, 0);

	VIBufferRenderer::Desc ground;
	ground.mtrlName = L"ground";
	ground.meshName = L"ground";
	auto groundObj = INSTANTIATE()->AddComponent<VIBufferRenderer>(&ground)->SetRotation(90, 0, 0);
	groundObj->GetComponent<VIBufferRenderer>()->SetFrustumCulling(false);

	INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>();
	m_pMainCamera = Core::GetInstance()->GetMainCamera();
	
	if (m_pMainCamera)
	{
		SmoothFollow::Desc follow_desc;
		follow_desc.minDistance = 5.f;
		follow_desc.maxDistance = 10.f;
		follow_desc.followRotationSpeed = 15.f;
		follow_desc.toTarget = PlayerInfoManager::GetInstance()->GetPlayer();

		
		m_pMainCamera->AddComponent<FieldCameraInfo>();
		m_pMainCamera->AddComponent<SmoothFollow>(&follow_desc);
		m_pMainCamera->AddComponent<StateControl>();
		m_pMainCamera->GetComponent<StateControl>()->AddState<FieldCameraSmoothFollowState>(L"CameraFollow");
		m_pMainCamera->GetComponent<StateControl>()->AddState<FieldCameraStartState>(L"CameraStart");
		m_pMainCamera->GetComponent<StateControl>()->AddState<FieldCameraNearEnemyState>(L"CameraNearEnemy");

		m_pMainCamera->GetComponent<StateControl>()->InitState(L"CameraFollow");
	}


	m_StageManager = StageManager::GetInstance()->GetGameObject();
	StageManager::GetInstance()->Set_StateControl();
	StageManager::GetInstance()->Get_StateControl()->AddState<DogFight_Stage1>(L"Tutorial");
	StageManager::GetInstance()->Get_StateControl()->InitState(L"Tutorial");
	
}
