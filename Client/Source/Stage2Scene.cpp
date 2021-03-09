#include "stdafx.h"
#include "..\Include\Stage2Scene.h"
#include "StageManager.h"
#include "DogFight_Stage1.h"
#include "DogFightState.h"
#include "EvasionState.h"
#include "BossState.h"

#include "FieldCameraInfo.h"
#include "SmoothFollow.h"

#include "FieldCameraSmoothFollowState.h"
#include "FieldCameraStartState.h"
#include "FieldCameraNearEnemyState.h"

#include "Camera_Evasion.h"
#include "Camera_Boss.h"
#include "Camera_Boss_Appear.h"

#include "Stage2_Mainstream_Define.h"
#include "Stage2_Mainstream_Headers.h"

#include "UIFactory.h"

Stage2Scene::Stage2Scene()
{
}


Stage2Scene::~Stage2Scene()
{
}

void Stage2Scene::Initialize()
{
	Core::GetInstance()->SetSkyBox(L"SkyBox1");

	INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	INSTANTIATE()->AddComponent<Grid>();

	DirectionalLight::Desc light;
	light.diffuseIntensity = 0.6f;
	light.ambientIntensity = 0.02f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(70, 180, 0);

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
		auto player = PlayerInfoManager::GetInstance()->GetPlayer();
		follow_desc.toTarget = player;

		m_pMainCamera->AddComponent<FieldCameraInfo>();
		m_pMainCamera->AddComponent<SmoothFollow>(&follow_desc);
		m_pMainCamera->AddComponent<StateControl>();
		m_pMainCamera->GetComponent<StateControl>()->AddState<FieldCameraSmoothFollowState>(L"CameraFollow");
		m_pMainCamera->GetComponent<StateControl>()->AddState<FieldCameraStartState>(L"CameraStart");
		m_pMainCamera->GetComponent<StateControl>()->AddState<FieldCameraNearEnemyState>(L"CameraNearEnemy");

		m_pMainCamera->GetComponent<StateControl>()->AddState<Camera_Evasion>(L"CameraEvasion");

		m_pMainCamera->GetComponent<StateControl>()->AddState<Camera_Boss_Appear>(L"CameraBoss_Appear");
		m_pMainCamera->GetComponent<StateControl>()->AddState<Camera_Boss>(L"CameraBoss");

		m_pMainCamera->GetComponent<StateControl>()->InitState(L"CameraFollow");
	}

	m_StageManager = StageManager::GetInstance()->GetGameObject();
	StageManager::GetInstance()->Set_StateControl();
	StageManager::GetInstance()->Get_StateControl()->AddState<DogFightState>(L"Dog_Fight");
	StageManager::GetInstance()->Get_StateControl()->AddState<EvasionState>(L"Evasion");
	StageManager::GetInstance()->Get_StateControl()->AddState<BossState>(L"Boss");
	StageManager::GetInstance()->Get_StateControl()->InitState(L"Dog_Fight");



	StageManager::GetInstance()->Get_StateControl()->AddState<State_Evasion_Enter>(_sn_enter);
}
