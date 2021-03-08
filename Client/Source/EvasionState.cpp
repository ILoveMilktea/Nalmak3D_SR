#include "stdafx.h"
#include "..\Include\EvasionState.h"

#include "EnemyManager.h"
#include "StageManager.h"

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
	m_pMainCamera->GetComponent<StateControl>()->SetState(L"CameraEvasion");

	m_pPlayer = PlayerInfoManager::GetInstance()->GetPlayer();
	PlayerInfoManager::GetInstance()->SetTimeLimit(m_fEvasionTime);
	PlayerInfoManager::GetInstance()->SetScore(m_fEvasiontScore);
	m_pPlayer->GetComponent<StateControl>()->SetState(L"playerEvasion_Enter");

	//m_Player->GetTransform()->fixRotationX = true;
	//m_Player->GetTransform()->fixRotationY = true;
	//m_Player->GetTransform()->fixRotationZ = true;

	m_Player->GetTransform()->SetScale(Vector3(0.4f, 0.4f, 0.4f));

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

	if (m_bEnter)
	{
		if (m_pPlayer->GetComponent<StateControl>()->GetCurStateString() == L"playerEvasion_Move")
		{
			m_bEnter = false;
		}
	}

	if (!m_bEnter)
	{
		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F6))
		{
			EnemyManager::GetInstance()->MidBoss_Spawn(IDLE);
		}

		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F7))
		{
			EnemyManager::GetInstance()->Enemy_Spwan_Evasion(CIRCLE);
		}
		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F8))
		{
			EnemyManager::GetInstance()->Enemy_Spwan_Evasion(PRYMIDE);
		}




		if (EnemyManager::GetInstance()->Get_EnemyCount() <= 0)
		{
			if (!m_bNext)
			{
				m_pPlayer->GetComponent<StateControl>()->SetState(L"playerEvasion_Exit");
				m_bNext = true;
			}

			wstring temp = m_pPlayer->GetComponent<StateControl>()->GetCurStateString();
			if (temp == L"playerBoss_Enter")
			{
				StageManager::GetInstance()->ToScene(L"Boss");
			}
		}


	}



	//DEBUG_LOG(L"Current Combat State : ", L"Evasion State");
	//DEBUG_LOG(L"MainCam POS", m_pMainCamera->GetGameObject()->GetTransform()->position);
	//DEBUG_LOG(L"MainCam Rotx", m_pMainCamera->GetGameObject()->GetTransform()->rotation.x);
	//DEBUG_LOG(L"MainCam Roty", m_pMainCamera->GetGameObject()->GetTransform()->rotation.y);
	//DEBUG_LOG(L"MainCam Rotz", m_pMainCamera->GetGameObject()->GetTransform()->rotation.z);
	//DEBUG_LOG(L"Player Rotz", m_Player->GetTransform()->rotation.z);

	m_fEvasionTime += dTime;
}

void EvasionState::ExitState()
{

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

void EvasionState::SceneToBoss()
{
	StageManager::GetInstance()->ToScene(L"Boss");
}
