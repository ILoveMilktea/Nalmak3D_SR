#include "stdafx.h"
#include "..\Include\DogFight_Stage2_1.h"

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

#include "Stage2_Mainstream_Define.h"

DogFight_Stage2_1::DogFight_Stage2_1()
{

}


DogFight_Stage2_1::~DogFight_Stage2_1()
{
}

void DogFight_Stage2_1::Initialize()
{

}

void DogFight_Stage2_1::EnterState()
{
	//INSTANTIATE(OBJECT_TAG_DEBUG, L"systemInfo")->AddComponent<SystemInfo>()->SetPosition(50, 50, 0);
	//INSTANTIATE()->AddComponent<Grid>();

#pragma region WeaponTest
	//ItemManager::GetInstance()->BuyItem(L"Weapon", L"AimMissile");
	//PlayerInfoManager::GetInstance()->EquipItem(FIRST_PARTS, L"Weapon", L"AimMissile");

	//ItemManager::GetInstance()->BuyItem(L"Weapon", L"Player_Weapon_Homing");
	//PlayerInfoManager::GetInstance()->EquipItem(FIRST_PARTS, L"Weapon", L"Player_Weapon_Homing");

	//ItemManager::GetInstance()->BuyItem(L"Weapon", L"ClusterMissile");
	//PlayerInfoManager::GetInstance()->EquipItem(FIRST_PARTS, L"Weapon", L"ClusterMissile");

	//ItemManager::GetInstance()->BuyItem(L"Weapon", L"Emp");
	//PlayerInfoManager::GetInstance()->EquipItem(FIRST_PARTS, L"Weapon", L"Emp");
#pragma endregion

	m_pMainCamera = Core::GetInstance()->GetMainCamera();

	auto infoManager = PlayerInfoManager::GetInstance();
	m_pPlayer = infoManager->GetPlayer();
	infoManager->SetTimeLimit(2000.f);
	infoManager->SetScore(0.f);


	EnemyManager::GetInstance()->Spawn_S1P1_Normal();
	m_bPattern1[0] = true;

}


void DogFight_Stage2_1::UpdateState()
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
				//StageManager::GetInstance()->ToScene(L"Evasion");
				
				StageManager::GetInstance()->ToScene(_sn_enter);
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

void DogFight_Stage2_1::ExitState()
{
	//DESTROY(Core::GetInstance()->FindObjectByName(0, L"SmoothFollow"));




}

float DogFight_Stage2_1::Get_Time() const
{
	return m_fDogFightTime;
}

float DogFight_Stage2_1::Get_Score() const
{
	return m_fDogFightScore;
}

void DogFight_Stage2_1::Set_Score(float _score)
{
	m_fDogFightScore = _score;
}

void DogFight_Stage2_1::Add_Score(float _score)
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
