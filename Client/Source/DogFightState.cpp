#include "stdafx.h"
#include "..\Include\DogFightState.h"

#include "PlayerInfoManager.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerTopViewMove.h"

#include "FixToTarget.h"
#include "MouseOption.h"
#include "SmoothFollow.h"

#include "EnemyManager.h"
#include "PlayerKitSelector.h"
#include "Bullet_Manager.h"

#include "StageManager.h"
#include "UIWindowFactory.h"
#include "SceneChanger.h"

DogFightState::DogFightState()
{

}


DogFightState::~DogFightState()
{
}

void DogFightState::Initialize()
{

}

void DogFightState::EnterState()
{
	INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	INSTANTIATE()->AddComponent<Grid>();

	m_Player = INSTANTIATE(OBJECT_TAG_PLAYER, L"player");
	m_Player->SetScale(0.1f, 0.1f, 0.1f);

	m_Player->AddComponent<StateControl>();
	m_Player->GetComponent<StateControl>()->AddState<PlayerIdle>(L"playerIdle");
	m_Player->GetComponent<StateControl>()->AddState<PlayerMove>(L"playerMove");
	m_Player->GetComponent<StateControl>()->AddState<PlayerTopViewMove>(L"playerTopViewMove");
	m_Player->GetComponent<StateControl>()->InitState(L"playerIdle");

	MeshRenderer::Desc render;
	render.mtrlName = L"default"; // 210223ȭ 12:50 ������ ������ �ȳ��ͼ� ���� �ٲ���
	render.meshName = L"flight";
	m_Player->AddComponent<MeshRenderer>(&render);
	m_Player->AddComponent<DrawGizmo>();
	m_Player->AddComponent<MouseOption>();

	SphereCollider::Desc player_col;
	player_col.radius = 1.f;
	m_Player->AddComponent<SphereCollider>();

	//m_Player->AddComponent<PlayerToTopView>();

	/*SceneChanger::Desc SceneChangerDescInfo;
	SceneChangerDescInfo.keyState = KEY_STATE_ENTER;
	SceneChangerDescInfo.sceneName = L"garage";
	auto SceneSelect = INSTANTIATE()->AddComponent<SceneChanger>(&SceneChangerDescInfo);
	*/

	PlayerInfoManager::GetInstance()->SetPlayer(m_Player);

	auto smoothFollow = INSTANTIATE(0, L"SmoothFollow");
	SmoothFollow::Desc smoothFollowDesc;
	smoothFollowDesc.toTarget = m_Player;
	smoothFollow->AddComponent<SmoothFollow>(&smoothFollowDesc);

	m_MainCamera = Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA);

	UIWindowFactory::DogfightStageWindow();

	EnemyManager::GetInstance();
}


void DogFightState::UpdateState()
{
	DEBUG_LOG(L"Current Combat State : ", L"Dog Fight State");

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F1))
	{
	}

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F2))
	{
		SceneToEvasion();
	}



	if (m_bProduce)
	{
		Accelerate();
		Player_Faraway();

		Vector3 Dir = m_Player->GetTransform()->position - vPlayerOrigin;

		if (D3DXVec3Length(&Dir) >= 1100.f)
		{
			StageManager::GetInstance()->ToScene(L"Evasion");
		}
	}

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F3))
	{
		Bullet_Manager::GetInstance()->Fire_Gun(Vector3(0, 0, 0), Quaternion(0, 0, 0, 0));
	}
}

void DogFightState::ExitState()
{
	//DESTROY(Core::GetInstance()->FindObjectByName(0, L"SmoothFollow"));
	m_Player->GetComponent<StateControl>()->SetState(L"playerTopViewMove");
}

void DogFightState::SceneToEvasion()
{
	if (!m_bProduce)
	{
		Vector3 PosTemp = Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->position;
		Quaternion RotTemp = Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->rotation;


		DESTROY(Core::GetInstance()->FindObjectByName(0, L"SmoothFollow"));


		m_MainCamera->GetTransform()->position = PosTemp;
		m_MainCamera->GetTransform()->rotation = RotTemp;

		vPlayerOrigin = m_Player->GetTransform()->position;

		m_bProduce = true;
	}
}

void DogFightState::Player_Faraway()
{
	Vector3 forward = m_Player->GetTransform()->GetForward();

	m_Player->GetTransform()->position += forward * m_fSpd;
}

void DogFightState::Accelerate()
{
	m_fSpd = Nalmak_Math::Lerp(m_fSpd, 5.f, dTime);
}
