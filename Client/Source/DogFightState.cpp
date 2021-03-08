#include "stdafx.h"
#include "..\Include\DogFightState.h"

#include "PlayerInfoManager.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"

#include "MouseOption.h"
#include "SmoothFollow.h"

#include "EnemyManager.h"
#include "Enemy_Bullet_Manager.h"

#include "StageManager.h"
#include "UIWindowFactory.h"
#include "SceneChanger.h"
#include "PlayerShooter.h"

#include "PlayerSkillActor.h"

#include "PlayerEscapeState.h"
#include "FieldCameraInfo.h"
#include "FieldCameraSmoothFollowState.h"
#include "FieldCameraStartState.h"
#include "FieldCameraNearEnemyState.h"
#include "FieldCameraEvationState.h"

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
	//INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	//INSTANTIATE()->AddComponent<Grid>();

#pragma region WeaponTest
	//ItemManager::GetInstance()->BuyItem(L"Weapon", L"AimMissile");
	//PlayerInfoManager::GetInstance()->EquipItem(FIRST_PARTS, L"Weapon", L"AimMissile");

	//ItemManager::GetInstance()->BuyItem(L"Weapon", L"Player_Weapon_Homing");
	//PlayerInfoManager::GetInstance()->EquipItem(FIRST_PARTS, L"Weapon", L"Player_Weapon_Homing");


#pragma region Player Particle

	//{
	//	ParticleRenderer::Desc render;
	//	render.particleDataName = L"player_zet_muzzle_left";
	//	m_Player->AddComponent<ParticleRenderer>(&render);
	//	render.particleDataName = L"player_zet_muzzle_right";
	//	m_Player->AddComponent<ParticleRenderer>(&render);
	//}
#pragma endregion







	//ItemManager::GetInstance()->BuyItem(L"Weapon", L"Emp");
	//PlayerInfoManager::GetInstance()->EquipItem(FIRST_PARTS, L"Weapon", L"Emp");
#pragma endregion

	m_pMainCamera = Core::GetInstance()->GetMainCamera();

	auto infoManager = PlayerInfoManager::GetInstance();
	auto player = infoManager->GetPlayer();



	infoManager->SetTimeLimit(m_fDogFightTime);
	infoManager->SetScore(m_fDogFightScore);

	infoManager->SetTimeLimit(2000.f);
	infoManager->SetScore(123456.f);
	infoManager->SetPlayer(player);


	player->AddComponent<UIInteractor>();
	UIWindowFactory::StageWindow(player);

	EnemyManager::GetInstance();

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

		m_fDogFightTime += dTime;

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






		if (m_bProduce && m_bNextPhase == false)
		{
			m_pPlayer->GetComponent<StateControl>()->SetState(L"playerFarAway");
			m_pMainCamera->GetComponent<SmoothFollow>()->SetActive(false);
			m_bNextPhase = true;
		}


		if (m_bNextPhase)
		{
			m_fProduceDelta += dTime;

			if (m_fProduceDelta >= 2.f)
			{
				StageManager::GetInstance()->ToScene(L"Evasion");
				m_fProduceDelta = 0.f;
				m_bNextPhase = false;
			}
		}






		//if (m_bProduce)
		//{
		//	Accelerate();
		//	Player_Faraway();

		//

		//	if (D3DXVec3Length(&Dir) >= 1100.f)
		//	{
		//		StageManager::GetInstance()->ToScene(L"Evasion");
		//	}
		//}



	DEBUG_LOG(L"Current Combat State : ", L"Dog Fight State");
}

void DogFightState::ExitState()
{
	//DESTROY(Core::GetInstance()->FindObjectByName(0, L"SmoothFollow"));




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



//void DogFightState::SceneToEvasion()
//{
//	if (!m_bProduce)
//	{
//		m_pPlayer->GetComponent<StateControl>()->SetState(L"playerNone");
//
//
//		if (Core::GetInstance()->FindObjectByName(0, L"SmoothFollow"))
//		{
//			Vector3 PosTemp = Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->position;
//			Quaternion RotTemp = Core::GetInstance()->FindObjectByName(0, L"SmoothFollow")->GetTransform()->rotation;
//
//			DESTROY(Core::GetInstance()->FindObjectByName(0, L"SmoothFollow"));
//
//			m_pMainCamera->GetTransform()->position = PosTemp;
//			m_pMainCamera->GetTransform()->rotation = RotTemp;
//		}
//
//
//		vPlayerOrigin = m_pPlayer->GetTransform()->position;
//
//		m_bProduce = true;
//	}
//}
//
//void DogFightState::Player_Faraway()
//{
//	Vector3 forward = m_pPlayer->GetTransform()->GetForward();
//
//	m_pPlayer->GetTransform()->position += forward * m_fSpd;
//}
//
//void DogFightState::Accelerate()
//{
//	//m_fSpd = Nalmak_Math::Lerp(m_fSpd, 5.f, dTime);
//	//if u using lerp, object will be slower in lowFrame Computer.
//
//	m_fSpd = dTime * 500.f;
//
//}
