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
#include "Bullet_Manager.h"

#include "StageManager.h"
#include "UIWindowFactory.h"
#include "SceneChanger.h"
#include "PlayerBossStageMove.h"
#include "PlayerNone.h"
#include "PlayerShooter.h"

// playerskill ?œì „??
#include "PlayerSkillActor.h"

//?¤í‚¬ ?íƒœë³??íƒœ
#include "PlayerEscapeState.h"
#include "FieldCameraInfo.h"
// camera state ?•ë ¬
#include "FieldCameraSmoothFollowState.h"
#include "FieldCameraStartState.h"
#include "FieldCameraNearEnemyState.h"


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
	m_Player->SetScale(0.25f, 0.25f, 0.25f);

	m_Player->AddComponent<StateControl>();
	m_Player->GetComponent<StateControl>()->AddState<PlayerNone>(L"playerNone");
	m_Player->GetComponent<StateControl>()->AddState<PlayerIdle>(L"playerIdle");
	m_Player->GetComponent<StateControl>()->AddState<PlayerMove>(L"playerMove");
	m_Player->GetComponent<StateControl>()->AddState<PlayerTopViewMove>(L"playerTopViewMove");
	m_Player->GetComponent<StateControl>()->AddState<PlayerBossStageMove>(L"playerBossMove");

	// ?¤í‚¬ê´€?¤ëœ ?¤í…Œ?´íŠ¸
	m_Player->GetComponent<StateControl>()->AddState<PlayerEscapeState>(L"playerEscape");

	m_Player->GetComponent<StateControl>()->InitState(L"playerIdle");
	/*VIBufferRenderer::Desc renderinfo;
	renderinfo.mtrlName = L"default";
	renderinfo.meshName = L"flight";*/
	MeshRenderer::Desc render;
	render.mtrlName = L"f15_base"; // 210223È­ 12:50 ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½È³ï¿½ï¿½Í¼ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ù²ï¿½ï¿½ï¿½
	render.meshName = L"f15";


	m_Player->AddComponent<MeshRenderer>(&render);
	m_Player->AddComponent<DrawGizmo>();
	m_Player->AddComponent<MouseOption>();
	m_Player->AddComponent<PlayerShooter>();
	m_Player->AddComponent<PlayerSkillActor>();
	SphereCollider::Desc player_col;
	player_col.radius = 1.f;
	m_Player->AddComponent<SphereCollider>();

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


	// ì¹´ë©”???¤í…Œ?´íŠ¸?ì„œ ê´€ë¦¬í•´ì¤?
	/*auto smoothFollow = INSTANTIATE(0, L"SmoothFollow");
	SmoothFollow::Desc smoothFollowDesc;
	smoothFollowDesc.toTarget = m_Player;
	smoothFollow->AddComponent<SmoothFollow>(&smoothFollowDesc);*/

	
	{
		m_MainCamera = Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA);
		if (m_MainCamera)
		{
			SmoothFollow::Desc followInfo;
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

	{
		m_Player->AddComponent<UIInteractor>();
		UIWindowFactory::StageWindow(m_Player);
	}
	


	{
		EnemyManager::GetInstance();

		ENEMY_STATUS tStatus(10, 20, 1);
		BULLET_STATUS tGun(0, 10, 50, 3, 180, 100, 0);
		BULLET_STATUS tMissile(10, 50, 5, 10, 30, 50, 0);

		EnemyManager::GetInstance()->Enemy_Spawn(Vector3(0.f, -30.f, 100.f), ENEMY_STATE::IDLE, tStatus, tGun, tMissile);

	}
	

}


void DogFightState::UpdateState()
{
	++m_iFrame;
	if (m_iFrame > 0)
	{
		//if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F1) )
		//{
		//	ENEMY_STATUS tStatus(10, 20, 1);
		//	BULLET_STATUS tGun(0, 10, 50, 3, 180, 100, 0);
		//	BULLET_STATUS tMissile(10, 50, 5, 10, 30, 50, 0);


		//	EnemyManager::GetInstance()->Enemy_Spawn(Vector3(-100.f, 50.f, 100.f), ENEMY_STATE::HOLD,
		//		tStatus, tGun, tMissile);
		//}
		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F1))
		{
			ENEMY_STATUS tStatus(10, 20, 1);
			BULLET_STATUS tGun(0, 10, 50, 3, 180, 100, 0);
			BULLET_STATUS tMissile(10, 50, 5, 10, 30, 50, 0);


			EnemyManager::GetInstance()->Enemy_Spawn(Vector3(100.f, 100.f, 100.f), ENEMY_STATE::CHASE,
				tStatus, tGun, tMissile);
		}

		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F2))
		{
			ENEMY_STATUS tStatus(10, 20, 1);
			BULLET_STATUS tGun(0, 10, 50, 3, 180, 100, 0);
			BULLET_STATUS tMissile(10, 50, 5, 10, 30, 50, 0);


			EnemyManager::GetInstance()->Enemy_Spawn(Vector3(-50.f, -20.f, 150.f), ENEMY_STATE::DROP,
				tStatus, tGun, tMissile);
		}

		//if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F4))
		//{
		//	EnemyManager::GetInstance()->Destroy_AllEnemy();
		//}



		//int i = EnemyManager::GetInstance()->Get_EnemyCount();

		if (EnemyManager::GetInstance()->Get_EnemyCount() <= 0)
		{
			SceneToEvasion();
		}
		//ì§€ê¸?Enter?ì„œ ?ë„ˆë¯??ì„±?˜ë©´ newGameobjectList???´ê¸°?ˆê¹Œ
		//gameobjectlist?ëŠ” Enemyê°€ ?†ìœ¼??ë°”ë¡œ ScenetoEvasion?¼ë¡œ ?˜ì–´??
		//ê·¸ë¦¬ê³??˜ì„œ Player??newGameObjectList???ˆìœ¼??ëª?ì°¾ì•„?€???…ê?.


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
	//monster?????†ì• ê¸?



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
