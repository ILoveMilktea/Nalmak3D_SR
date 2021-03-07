#include "stdafx.h"
#include "..\Include\DogFightState.h"

#include "PlayerInfoManager.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerTopViewMove.h"


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

#include "PlayerSkillActor.h"

#include "PlayerEscapeState.h"
#include "FieldCameraInfo.h"
#include "FieldCameraSmoothFollowState.h"
#include "FieldCameraStartState.h"
#include "FieldCameraNearEnemyState.h"


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
	infoManager->SetTimeLimit(m_fDogFightTime);
	infoManager->SetScore(m_fDogFightScore);

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



			//플레이어 farAway iState로 빼주고, 거리 계속 반환 받아서 원래 거리보다 얼마 이상 가면
			//TopViewCamera로 MainCamera state 바꿔주고
			//씬 넘기기
			//씬 넘기고 나서 플레이어 들어오는걸로 State바꿔주고
			//일정 거리에 도달하면 몬스터 생성하고 스테이지 시작.
			//일정 시간 버티고나면 보스몹 생성하고
			//카메라 쉐이킹 넣으면서
			//보스몹 다가오는 state로 바꿔준다음에 일정거리 이상 들어오면
			//보스필드 전용 카메라로 연출 해준 뒤 시작.
			
		


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
