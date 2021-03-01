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
	m_MainCamera = Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA);

	if (m_MainCamera == nullptr)
	{
		assert(L"아 ㅋㅋ 메인 카메라 못찾겠다고 ㅋㅋ");
	}
	
	m_MainCamera->SetPosition(0.f, 100.f, 0.f);
	m_MainCamera->SetRotation(0.f, 0.f, 0.f);
	m_MainCamera->GetTransform()->RotateX(90.f);
	//컴포넌트 넣어서 
	
	m_Player = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);
	if (m_Player == nullptr)
	{
		assert(L"플레이어 못받은거 같은데여 ㅋㅋ;;");
	}
	m_Player->GetTransform()->position = Vector3(0, 0, -50);
	m_Player->GetTransform()->SetRotation(0, 0, 0);

	ENEMY_STATUS tStatus(10, 20, 1);
	BULLET_STATUS tGun(0, 10, 50, 3, 180, 100, 0);
	BULLET_STATUS tMissile(10, 50, 5, 10, 30, 50, 0);
	
	EnemyManager::GetInstance()->Enemy_Spawn(Vector3(-20.f, 0.f, 30.f), ENEMY_STATE::IDLE, tStatus, tGun, tMissile);

	m_bEnter = true;

	// UI test
	CanvasGroup::GetInstance()->SetObjectActive(CANVAS_GROUP_STAGE1, false);
}

void EvasionState::UpdateState()
{
	EnterProduce();
		
	if (!m_bEnter)
	{
		if (EnemyManager::GetInstance()->Get_EnemyCount() <= 0
			/*InputManager::GetInstance()->GetKeyDown(KEY_STATE_F2)*/)
		{
			SceneToBoss();
		}
	}


		
	DEBUG_LOG(L"Current Combat State : ", L"Evasion State");
	DEBUG_LOG(L"MainCam POS", m_MainCamera->GetTransform()->position);
	DEBUG_LOG(L"MainCam Rotx", m_MainCamera->GetTransform()->rotation.x);
	DEBUG_LOG(L"MainCam Roty", m_MainCamera->GetTransform()->rotation.y);
	DEBUG_LOG(L"MainCam Rotz", m_MainCamera->GetTransform()->rotation.z);
	DEBUG_LOG(L"Player Rotz", m_Player->GetTransform()->rotation.z);

	m_fEvasionTime += dTime;
}

void EvasionState::ExitState()
{
	m_Player->GetComponent<StateControl>()->SetState(L"playerBossMove");

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
		m_Player->GetTransform()->position.z += dTime * 50.f;

		if (m_Player->GetTransform()->position.z >= 0.f)
		{
			m_bEnter = false;
		}
	}
}

void EvasionState::SceneToBoss()
{
	StageManager::GetInstance()->ToScene(L"Boss");
}
