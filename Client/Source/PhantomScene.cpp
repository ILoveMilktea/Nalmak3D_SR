#include "stdafx.h"
#include "..\Include\PhantomScene.h"
#include "NextSceneLoad.h"
#include "core.h"

#include "PlayerInfoManager.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"

#include "MouseOption.h"
#include "SmoothFollow.h"

#include "EnemyManager.h"

#include "StageManager.h"

#include "UIWindowFactory.h"
#include "FieldCameraInfo.h"
#include "FieldCameraSmoothFollowState.h"
#include "FieldCameraStartState.h"
#include "FieldCameraNearEnemyState.h"

PhantomScene::PhantomScene()
{

}


PhantomScene::~PhantomScene()
{
}

void PhantomScene::Initialize()
{
	//Core::GetInstance()->SetSkyBox(L"SkyBox1");

	//DirectionalLight::Desc light;
	//light.diffuseIntensity = 0.6f;
	//light.ambientIntensity = 0.02f;
	//INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(60, 180, 0);

	//VIBufferRenderer::Desc ground;
	//ground.mtrlName = L"ground";
	//ground.meshName = L"ground";
	//auto groundObj = INSTANTIATE()->AddComponent<VIBufferRenderer>(&ground)->SetRotation(90, 0, 0);
	//groundObj->GetComponent<VIBufferRenderer>()->SetFrustumCulling(false);


	//srand((unsigned int)time(NULL));

	//auto mainCam = INSTANTIATE(OBJECT_TAG_CAMERA, L"mainCamera")->AddComponent<Camera>();

	//StageManager::GetInstance();

	srand((unsigned int)time(NULL));

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

	INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	INSTANTIATE()->AddComponent<Grid>();

	m_Player = PlayerInfoManager::GetInstance()->GetPlayer();

	EnemyManager::GetInstance()->Enemy_Spawn_Test(CHASE,Vector3(50.f,50.f,100.f));
	EnemyManager::GetInstance()->Enemy_Spawn_Test(CHASE, Vector3(0.f, 0.f, 200.f));

	EnemyManager::GetInstance()->Enemy_Spawn_Test(CHASE, Vector3(150.f, 50.f, 200.f));
	EnemyManager::GetInstance()->Enemy_Spawn_Test(CHASE, Vector3(50.f, 150.f, 200.f));
	EnemyManager::GetInstance()->Enemy_Spawn_Test(CHASE, Vector3(50.f, 0.f, 200.f));


}
