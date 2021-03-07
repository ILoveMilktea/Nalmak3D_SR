#include "stdafx.h"
#include "..\Include\DogFight_Stage1.h"


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

// playerskill 시전자
#include "PlayerSkillActor.h"

//스킬 상태별 상태
#include "PlayerEscapeState.h"
#include "GameManager.h"


DogFight_Stage1::DogFight_Stage1()
{
}


DogFight_Stage1::~DogFight_Stage1()
{
}

void DogFight_Stage1::Initialize()
{

}

void DogFight_Stage1::EnterState()
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
	
	//ItemManager::GetInstance()->BuyItem(L"Weapon", L"Emp");f
	//PlayerInfoManager::GetInstance()->EquipItem(FIRST_PARTS, L"Weapon", L"Emp");
#pragma endregion

	m_pMainCamera = Core::GetInstance()->GetMainCamera();

	m_Player = PlayerInfoManager::GetInstance()->GetPlayer();
	PlayerInfoManager::GetInstance()->SetTimeLimit(m_fTutorialTime);
	PlayerInfoManager::GetInstance()->SetScore(m_fTutorialScore);


	EnemyManager::GetInstance();

	EnemyManager::GetInstance()->Spawn_S1P1_Normal();
	m_bPattern1[0] = true;
}

void DogFight_Stage1::UpdateState()
{
	m_fTutorialTime += dTime;

	if (m_bPattern1[0] == true && m_bPattern1[1] == false
		&& EnemyManager::GetInstance()->Get_EnemyCount() <= 0)
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
		m_bSceneChange = true;
	}


	





	



	
	if (m_bSceneChange && !GameManager::GetInstance()->Get_StageClear(1))
	{
		GameManager::GetInstance()->Set_StageClear(1);
		m_Player->GetComponent<StateControl>()->SetState(L"playerFarAway");
		m_pMainCamera->GetComponent<SmoothFollow>()->SetActive(false);
	}

	if (m_bSceneChange)
	{
		m_fProduceDelta += dTime;

		if (m_fProduceDelta >= 2.f)
		{
			Core::GetInstance()->LoadScene(L"result");
			m_fProduceDelta = 0.f;
			m_bSceneChange = false;
		}
	}

	DEBUG_LOG(L"Produce Delta", m_fProduceDelta);
	DEBUG_LOG(L"Current Combat State : ", L"Stage1 Phase1 : tutorial"); 
}

void DogFight_Stage1::ExitState()
{
	int i = 0;
}

float DogFight_Stage1::Get_Time() const
{
	return m_fTutorialTime;
}

float DogFight_Stage1::Get_Score() const
{
	return m_fTutorialScore;
}

void DogFight_Stage1::Set_Score(float _score)
{
	m_fTutorialScore = _score;
}

void DogFight_Stage1::Add_Score(float _score)
{
	m_fTutorialScore += _score;
}


void DogFight_Stage1::Player_Faraway()
{
	Vector3 forward = m_Player->GetTransform()->GetForward();

	m_Player->GetTransform()->position += forward * m_fSpd;
}

void DogFight_Stage1::Accelerate()
{
	m_fSpd = dTime * 500.f;
}