#include "stdafx.h"
#include "..\Include\EvasionState.h"

#include "EnemyManager.h"
#include "StageManager.h"
#include "PlayerTopViewMove.h"

EvasionState::EvasionState()
{
}


EvasionState::~EvasionState()
{
}

void EvasionState::Initialize()
{

}

void EvasionState::EnterState()
{
	m_pMainCamera = Core::GetInstance()->GetMainCamera();

	m_pPlayer = PlayerInfoManager::GetInstance()->GetPlayer();
	PlayerInfoManager::GetInstance()->SetTimeLimit(m_fEvasionTime);
	PlayerInfoManager::GetInstance()->SetScore(m_fEvasiontScore);

	ENEMY_STATUS tStatus(10, 20, 1);
	BULLET_STATUS tGun(0, 10, 50, 3, 180, 100, 0);
	BULLET_STATUS tMissile(10, 50, 5, 10, 30, 50, 0);
	
	EnemyManager::GetInstance()->Enemy_Spawn(Vector3(-20.f, 0.f, 30.f), Vector3(0.1f, 0.1f, 0.1f),
		ENEMY_STATE::IDLE, tStatus, tGun, tMissile);

	m_bEnter = true;

	// UI test
	CanvasGroup::GetInstance()->SetObjectActive(CANVAS_GROUP_STAGE1, false);
}

void EvasionState::UpdateState()
{
	//Enter에서 카메라 세팅, 그리고 플레이어 중앙으로.
	
	EnterProduce();
		
	if (!m_bEnter)
	{
		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F1))
		{
			EnemyManager::GetInstance()->Enemy_Spwan_Evasion(SLIDE);
		}

		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F2))
		{
			EnemyManager::GetInstance()->Enemy_Spwan_Evasion(DIAGONAL);
		}

		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F3))
		{
			EnemyManager::GetInstance()->Enemy_Spwan_Evasion(LOOK);
		}

		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F5))
		{
			EnemyManager::GetInstance()->Enemy_Spwan_Evasion(CROSSFIRE);
		}

		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F6))
		{
			EnemyManager::GetInstance()->Enemy_Spwan_Evasion(AIRFIRE);
		}

		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F7))
		{
			EnemyManager::GetInstance()->Enemy_Spwan_Evasion(CIRCLE);
		}
		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F8))
		{
			EnemyManager::GetInstance()->Enemy_Spwan_Evasion(PRYMIDE);
		}




		if (EnemyManager::GetInstance()->Get_EnemyCount() <= 0
			/*InputManager::GetInstance()->GetKeyDown(KEY_STATE_F2)*/)
		{
			SceneToBoss();
		}





	}


		
	//DEBUG_LOG(L"Current Combat State : ", L"Evasion State");
	//DEBUG_LOG(L"MainCam POS", m_MainCamera->GetTransform()->position);
	//DEBUG_LOG(L"MainCam Rotx", m_MainCamera->GetTransform()->rotation.x);
	//DEBUG_LOG(L"MainCam Roty", m_MainCamera->GetTransform()->rotation.y);
	//DEBUG_LOG(L"MainCam Rotz", m_MainCamera->GetTransform()->rotation.z);
	//DEBUG_LOG(L"Player Rotz", m_Player->GetTransform()->rotation.z);

	m_fEvasionTime += dTime;
}

void EvasionState::ExitState()
{
	m_pPlayer->GetComponent<StateControl>()->SetState(L"playerNone");

	EnemyManager::GetInstance()->Destroy_AllEnemy();
}

float EvasionState::Get_Time() const
{
	return m_fEvasionTime;
}

float EvasionState::Get_Score() const
{
	return m_fEvasiontScore;
}

void EvasionState::Set_Score(float _score)
{
	m_fEvasiontScore = _score;
}

void EvasionState::Add_Score(float _score)
{
	m_fEvasiontScore += _score;
}

void EvasionState::EnterProduce()
{
	if (m_bEnter)
	{
		m_pPlayer->GetTransform()->position.z += dTime * 50.f;

		if (m_pPlayer->GetTransform()->position.z >= 0.f)
		{
			m_pPlayer->GetComponent<StateControl>()->SetState(L"playerTopViewMove");
			m_bEnter = false;
		}
	}
}

void EvasionState::SceneToBoss()
{
	StageManager::GetInstance()->ToScene(L"Boss");
}
