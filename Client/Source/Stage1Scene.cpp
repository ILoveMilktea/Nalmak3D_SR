#include "stdafx.h"
#include "..\Include\Stage1Scene.h"
#include "StageManager.h"

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
#include "DogFight_Stage2_Enter.h"
#include "DogFight_Stage2_1.h"
#include "DogFight_Stage2_Exit.h"
#include "DogFight_Stage2_2.h"
#include "DogFight_Stage2_3.h"
#include "DogFight_Stage2_4.h"

#include "DogFight_Stage1_1.h"
#include "DogFight_Stage1_Enter.h"
#include "DogFight_Stage1_2.h"
#include "DogFight_Stage1_3.h"
#include "DogFight_Stage1_Exit.h"

#include "GameManager.h"




void Stage1Scene::Initialize()
{
	Core::GetInstance()->SetSkyBox(L"SkyBox1");

	INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	INSTANTIATE()->AddComponent<Grid>();

	DirectionalLight::Desc light;
	light.diffuseIntensity = 0.6f;
	light.ambientIntensity = 0.02f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(70, 180, 0);

	/*VIBufferRenderer::Desc ground;
	ground.mtrlName = L"ground";
	ground.meshName = L"ground";
	auto groundObj = INSTANTIATE()->AddComponent<VIBufferRenderer>(&ground)->SetRotation(90, 0, 0);
	groundObj->GetComponent<VIBufferRenderer>()->SetFrustumCulling(false);*/

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

	auto stateControl = StageManager::GetInstance()->GetComponent<StateControl>();
	/////////////////////////////////////////////////////////////////////////////////
	// stage1
	stateControl->AddState<DogFight_Stage1_Enter>(L"Tutorial_Enter");
	stateControl->AddState<DogFight_Stage1_1>(L"Tutorial_1");
	stateControl->AddState<DogFight_Stage1_2>(L"Tutorial_2");
	stateControl->AddState<DogFight_Stage1_3>(L"Tutorial_3");
	stateControl->AddState<DogFight_Stage1_Exit>(L"Tutorial_Exit");

	/////////////////////////////////////////////////////////////////////////////////
	// stage2
	stateControl->AddState<DogFight_Stage2_Enter>(L"DogFight_Enter");
	stateControl->AddState<DogFight_Stage2_1>(L"DogFight_1");
	stateControl->AddState<DogFight_Stage2_2>(L"DogFight_2");
	stateControl->AddState<DogFight_Stage2_3>(L"DogFight_3");
	stateControl->AddState<DogFight_Stage2_4>(L"DogFight_4");
	stateControl->AddState<DogFight_Stage2_Exit>(L"DogFight_Exit");

	stateControl->AddState<State_Evasion_Enter>(_sn_enter);
	stateControl->AddState<State_Evasion_Airfire>(_sn_airfire);
	stateControl->AddState<State_Evasion_Midboss>(_sn_midboss);
	stateControl->AddState<State_Evasion_MidbossDead>(_sn_midbossdead);

	//stateControl->AddState<EvasionState>(L"Evasion");
	//stateControl->AddState<BossState>(L"Boss");
	/////////////////////////////////////////////////////////////////////////////////

	stateControl->InitState(GameManager::GetInstance()->Get_NextStage());
}
