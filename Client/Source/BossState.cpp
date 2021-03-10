#include "stdafx.h"
#include "..\Include\BossState.h"

#include "EnemyManager.h"
#include "UIWindowFactory.h"

BossState::BossState()
{
}


BossState::~BossState()
{
}

void BossState::Initialize()
{

}

void BossState::EnterState()
{
	m_pMainCamera = Core::GetInstance()->GetMainCamera();
	m_pMainCamera->GetComponent<StateControl>()->SetState(L"CameraBoss_Appear");

	m_pPlayer = PlayerInfoManager::GetInstance()->GetPlayer();
	PlayerInfoManager::GetInstance()->SetTimeLimit(m_fBossTime);
	PlayerInfoManager::GetInstance()->SetScore(m_fBossScore);
	m_pPlayer->GetComponent<StateControl>()->SetState(L"playerBoss_Enter");

	m_pBoss = EnemyManager::GetInstance()->Get_Boss();


	// ==== UI ====
	UIWindowFactory::BossUI();
	m_bossui = false;
	// ==== UI ====

	m_bEnter = true;
}

void BossState::UpdateState()
{
	m_fBossTime += dTime;
	

	

	//if (m_bEnter)
	//{
	//	if (EnterProduce())
	//	{
	//		m_pPlayer->GetComponent<StateControl>()->SetState(L"playerBossMove");
	//		m_bEnter = false;
	//	}
	//}
	//if (m_bEnter == false)
	//{
	//	if (/*EnemyManager::GetInstance()->Get_BossHp() <= 0*/ 
	//		EnemyManager::GetInstance()->Get_EnemyCount()<=0&& GameManager::GetInstance()->Get_StageClear(2) == false)
	//	{
	//		GameManager::GetInstance()->Set_StageClear(2);
	//		Core::GetInstance()->LoadScene(L"result");

	//		return;
	//	}
	//}
	//
	//DEBUG_LOG(L"Player Pos", m_pPlayer->GetTransform()->position);
	//DEBUG_LOG(L"Camera Pos", m_pMainCamera->GetTransform()->position);

	if (EnemyManager::GetInstance()->Get_EnemyCount() <= 0 && !m_bSceneChange)
	{
		Core::GetInstance()->LoadScene(L"result");
		m_bSceneChange = true;
	}

	DEBUG_LOG(L"Current Combat State : ", L"Boss State");
}

void BossState::ExitState()
{
}

float BossState::Get_Time() const
{
	return m_fBossTime;
}

float BossState::Get_Score() const
{
	return m_fBossScore;
}

void BossState::Set_Score(float _score)
{
	m_fBossScore = _score;
}

void BossState::Add_Score(float _score)
{
	m_fBossScore += _score;
}

bool BossState::EnterProduce()
{
	//1. player move to certain pos

	if (m_bPlayerSetting)
	{
		m_pPlayer->GetTransform()->position = Nalmak_Math::Lerp(m_pPlayer->GetTransform()->position, m_vPlayerInitPos, dTime * 2);
		m_pPlayer->GetTransform()->rotation.z = Nalmak_Math::Lerp(m_pPlayer->GetTransform()->rotation.z, 0.f, dTime);

		if (m_pPlayer->GetTransform()->position.x >= m_vPlayerInitPos.x - 0.1f
			&& m_pPlayer->GetTransform()->position.x <= m_vPlayerInitPos.x + 0.1f
			&& m_pPlayer->GetTransform()->position.y >= m_vPlayerInitPos.y - 0.1f
			&& m_pPlayer->GetTransform()->position.y <= m_vPlayerInitPos.y + 0.1f)
		{
			m_bPlayerSetting = false;
		}

		if (m_pPlayer->GetTransform()->position.x >= m_vPlayerInitPos.x - 5.f
			&& m_pPlayer->GetTransform()->position.x <= m_vPlayerInitPos.x + 5.f
			&& m_pPlayer->GetTransform()->position.y >= m_vPlayerInitPos.y - 5.f
			&& m_pPlayer->GetTransform()->position.y <= m_vPlayerInitPos.y + 5.f)
		{
			if (!m_bCameraShaking)
			{
				m_bCameraShaking = true;
				m_bBossMove = true;
				vCameraOrigin = m_pMainCamera->GetTransform()->position;
				m_pBoss = Core::GetInstance()->FindObjectByName(OBJECT_TAG_BOSS, L"Boss");
			}
		}
	}

	//2. Camera shaking
	if (m_bCameraShaking)
	{
		m_pMainCamera->GetTransform()->position = RandForShaking() * fShakingForce + vCameraOrigin;
		fShakingTime -= dTime;


	}

	//3. Boss Appear
	if (m_pBoss && m_bBossMove)
	{
		m_pBoss->GetTransform()->position.z -= dTime * 10.f;

		if (m_pBoss->GetTransform()->position.z <= 150.f && m_pBoss->GetTransform()->position.z > 100.f)
		{
			m_bPlayerMove = true;
		}

		if (m_bPlayerMove)
		{
			m_pPlayer->GetTransform()->position.z -= dTime *10.f;

			if (m_pBoss->GetTransform()->position.z <= 100.f)
			{
				m_bBossMove = false;
				m_bPlayerMove = false;
				m_bCameraShaking = false;
				m_bCameraProduce = true;

				if (!m_bossui)
				{
					m_bossui = true;
					list<CanvasRenderer*> group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_BOSSHP);

					for (auto ui : group)
					{
						BossUIAnimator* animator = ui->GetComponent<BossUIAnimator>();

						if (animator)
						{
							animator->StartMoveDown(160.f);
						}
					}
				}
			}
		}
	}

	if (m_bCameraProduce)
	{
		m_pPlayer->GetTransform()->rotation.z = 0.f;

		m_pMainCamera->GetTransform()->position.z
			= Nalmak_Math::Lerp(m_pMainCamera->GetTransform()->position.z,
				m_pPlayer->GetTransform()->position.z - 50.f, dTime);

		m_pMainCamera->GetTransform()->position.y
			= Nalmak_Math::Lerp(m_pMainCamera->GetTransform()->position.y,
				0.f, dTime);

		m_pMainCamera->GetTransform()->SetRotationX(0);

		if (m_pMainCamera->GetTransform()->position.y <= 0.02f)
		{
			m_bCameraProduce = false;

			m_pMainCamera->GetTransform()->position = Vector3(0.f, 0.f, -100.f);
			m_pPlayer->GetTransform()->position = Vector3(0.f, 0.f, -50.f);


			return true;
		}
	}
	return false;


	//4. Camera Moving
}

const Vector3 & BossState::RandForShaking()
{
	return vCameraRand = Vector3(rand() % 3 - 1.f, rand() % 3 - 1.f, rand() % 3 - 1.f);
}

void BossState::CameraShaking()
{
}

void BossState::BossAppear()
{
}
