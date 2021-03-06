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
#include "Enemy_Bullet_Manager.h"

#include "StageManager.h"
#include "UIWindowFactory.h"
#include "SceneChanger.h"
#include "PlayerBossStageMove.h"
#include "PlayerNone.h"
#include "PlayerShooter.h"

// playerskill ?�전??
#include "PlayerSkillActor.h"

//?�킬 ?�태�??�태
#include "PlayerEscapeState.h"
#include "FieldCameraInfo.h"
// camera state ?�렬
#include "FieldCameraSmoothFollowState.h"
#include "FieldCameraStartState.h"
#include "FieldCameraNearEnemyState.h"


#include "Player_WindEffect.h"

#include "Player_WindEffect.h"

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

	//ItemManager::GetInstance()->BuyItem(L"Weapon", L"AimMissile");
	//PlayerInfoManager::GetInstance()->EquipItem(PARTS_NUM::FIRST_PARTS, L"Weapon", L"AimMissile");

	//ItemManager::GetInstance()->BuyItem(L"Weapon", L"Player_Weapon_Homing");
	//PlayerInfoManager::GetInstance()->EquipItem(FIRST_PARTS, L"Weapon", L"Player_Weapon_Homing");

	m_Player = INSTANTIATE(OBJECT_TAG_PLAYER, L"player");

	m_Player->SetScale(0.2f, 0.2f, 0.2f);
#pragma region Player Particle

	{
		ParticleRenderer::Desc render;
		render.particleDataName = L"player_zet_muzzle_left";
		m_Player->AddComponent<ParticleRenderer>(&render);
		render.particleDataName = L"player_zet_muzzle_right";
		m_Player->AddComponent<ParticleRenderer>(&render);
	}
#pragma endregion

	{
		PointLight::Desc lightDesc;
		lightDesc.color = Vector3(1, 0.3f, 0);
		lightDesc.radius = 2.f;
		lightDesc.diffuseIntensity = 5.f;
		auto light = INSTANTIATE()->AddComponent<PointLight>(&lightDesc)->SetPosition(0, 0, -1.5f);
		light->SetParents(m_Player);

	}
	Player_WindEffect::Desc wind;
	wind.leftTrailPos = Vector3(-1.8f, 0.14f, -0.01f);
	wind.rightTrailPos = Vector3(1.8f, 0.14f, -0.01f);
	wind.trailThick = 0.2f;
	m_Player->AddComponent<Player_WindEffect>(&wind);

	m_Player->AddComponent<StateControl>();
	m_Player->GetComponent<StateControl>()->AddState<PlayerNone>(L"playerNone");
	m_Player->GetComponent<StateControl>()->AddState<PlayerIdle>(L"playerIdle");
	m_Player->GetComponent<StateControl>()->AddState<PlayerMove>(L"playerMove");
	m_Player->GetComponent<StateControl>()->AddState<PlayerTopViewMove>(L"playerTopViewMove");
	m_Player->GetComponent<StateControl>()->AddState<PlayerBossStageMove>(L"playerBossMove");

	m_Player->GetComponent<StateControl>()->AddState<PlayerEscapeState>(L"playerEscape");

	m_Player->GetComponent<StateControl>()->InitState(L"playerIdle");

	MeshRenderer::Desc render;
	render.mtrlName = L"f15";
	render.meshName = L"f15";
	m_Player->AddComponent<MeshRenderer>(&render);
	m_Player->AddComponent<PlayerShooter>();
	m_Player->AddComponent<PlayerSkillActor>();
	SphereCollider::Desc player_col;
	player_col.radius = 1.f;
	//m_Player->AddComponent<SphereCollider>();

	//ParticleRenderer::Desc particle;
	//particle.particleDataName = L"20mmCannon";
	//m_Player->AddComponent<ParticleRenderer>(&particle);

	//m_Player->AddComponent<PlayerToTopView>();

	/*SceneChanger::Desc SceneChangerDescInfo;
	SceneChangerDescInfo.keyState = KEY_STATE_ENTER;
	SceneChangerDescInfo.sceneName = L"garage";
	auto SceneSelect = INSTANTIATE()->AddComponent<SceneChanger>(&SceneChangerDescInfo);
	*/

	auto infoManager = PlayerInfoManager::GetInstance();
	infoManager->SetTimeLimit(2000.f);
	infoManager->SetScore(123456.f);
	infoManager->SetPlayer(m_Player);


	// 카메???�테?�트?�서 관리해�?
	/*auto smoothFollow = INSTANTIATE(0, L"SmoothFollow");
	SmoothFollow::Desc smoothFollowDesc;
	smoothFollowDesc.toTarget = m_Player;
	smoothFollow->AddComponent<SmoothFollow>(&smoothFollowDesc);*/


	{
		m_MainCamera = Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA);
		if (m_MainCamera)
		{
			SmoothFollow::Desc followInfo;
			followInfo.minDistance = 5.f;
			followInfo.maxDistance = 10.f;
			followInfo.followRotationSpeed = 15.f;
			followInfo.toTarget = m_Player;

			//auto cameraStateControl = INSTANTIATE(OBJECT_TAG_CAMERA)
			m_MainCamera->AddComponent<FieldCameraInfo>();
			m_MainCamera->AddComponent<SmoothFollow>(&followInfo);
			m_MainCamera->AddComponent<StateControl>();
			m_MainCamera->GetComponent<StateControl>()->AddState<FieldCameraSmoothFollowState>(L"CameraFollow");
			m_MainCamera->GetComponent<StateControl>()->AddState<FieldCameraStartState>(L"CameraStart");
			m_MainCamera->GetComponent<StateControl>()->AddState<FieldCameraNearEnemyState>(L"CameraNearEnemy");
			m_MainCamera->GetComponent<StateControl>()->InitState(L"CameraFollow");
		}
	}
	//smoothFollowDesc.minDistance = 5.f;
	//smoothFollowDesc.maxDistance = 10.f;
	//smoothFollowDesc.followRotationSpeed = 15.f;

	//smoothFollow->AddComponent<SmoothFollow>(&smoothFollowDesc);

	{
		m_Player->AddComponent<UIInteractor>();
		UIWindowFactory::StageWindow(m_Player);
	}



	//ENEMY_STATUS tStatus(10, 20, 1);
	//BULLET_STATUS tGun(0, 10, 50, 3, 180, 100, 0);
	//BULLET_STATUS tMissile(10, 50, 5, 10, 30, 50, 0);

	//EnemyManager::GetInstance()->Enemy_Spawn(Vector3(0.f, 0.f, 100.f), Vector3(0.1f, 0.1f, 0.1f), ENEMY_STATE::IDLE, tStatus, tGun, tMissile);

	//EnemyManager::GetInstance()->Player_FovSpawnTest(true, 100.f);
	EnemyManager::GetInstance()->Spawn_S1P1_Normal();
	m_bPattern1[0] = true;
}


void DogFightState::UpdateState()
{
	++m_iFrame;
	if (m_iFrame > 0)
	{
		if (m_bPattern1[0] == true && m_bPattern1[1] == false
			&& EnemyManager::GetInstance()->Get_EnemyCount() <= 0 )
		{
			m_bPattern1[1] = true;
		}

		if (m_bPattern1[1] == true && m_bPattern2[0] == false)
		{
			EnemyManager::GetInstance()->Spawn_S1P1_Huge();
			m_bPattern2[0] = true;
		}

		if (m_bPattern2[0] == true && m_bPattern2[1] == false
			&& EnemyManager::GetInstance()->Get_EnemyCount() <= 0)
		{
			m_bPattern2[1] = true;
		}

		if (m_bPattern2[1] == true && m_bPattern3[0] == false
			&& EnemyManager::GetInstance()->Get_EnemyCount() <= 0)
		{
			EnemyManager::GetInstance()->Spawn_S1P1_Quick();
			m_bPattern3[0] = true;
		}

		if (m_bPattern3[0] == true && m_bPattern3[1] == false
			&& EnemyManager::GetInstance()->Get_EnemyCount() <= 0)
		{
			m_bPattern3[1] = true;
			m_bProduce = true;
		}








		//if (EnemyManager::GetInstance()->Get_EnemyCount() <= 0)
		//{
		//	SceneToEvasion();
		//}
		//지금 Enter에서 에너미 생성하면 newGameobjectList에 담기니까
		//gameobjectlist에는 Enemy가 없으니 바로 ScenetoEvasion으로 넘어옴.
		//그리고 나서 Player도 newGameObjectList에 있으니 못 찾아와서 팅김.

		if (m_bPattern3[0] == true && m_bPattern3[1] == false
			&& EnemyManager::GetInstance()->Get_EnemyCount() <= 0)
		{
			m_bPattern3[1] = true;
			m_bProduce = true;
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

		m_fDogFightTime += dTime;
	}
	DEBUG_LOG(L"Current Combat State : ", L"Dog Fight State");
}

void DogFightState::ExitState()
{
	//DESTROY(Core::GetInstance()->FindObjectByName(0, L"SmoothFollow"));
	//monster?????�애�?



}

float DogFightState::Get_Time() const
{
	return m_fDogFightTime;
}

float DogFightState::Get_Score() const
{
	return m_fDogFightScore;
}

void DogFightState::Set_Score(float _score)
{
	m_fDogFightScore = _score;
}

void DogFightState::Add_Score(float _score)
{
	m_fDogFightScore += _score;
}



void DogFightState::SceneToEvasion()
{
	if (!m_bProduce)
	{
		m_Player->GetComponent<StateControl>()->SetState(L"playerNone");


		if (Core::GetInstance()->FindObjectByName(0, L"SmoothFollow"))
		{
			Vector3 PosTemp = Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->position;
			Quaternion RotTemp = Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->rotation;

			DESTROY(Core::GetInstance()->FindObjectByName(0, L"SmoothFollow"));

			m_MainCamera->GetTransform()->position = PosTemp;
			m_MainCamera->GetTransform()->rotation = RotTemp;
		}


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
	//m_fSpd = Nalmak_Math::Lerp(m_fSpd, 5.f, dTime);
	//if u using lerp, object will be slower in lowFrame Computer.

	m_fSpd = dTime * 500.f;

}
