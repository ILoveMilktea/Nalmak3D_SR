#include "stdafx.h"
#include "..\Include\BossState.h"

#include "EnemyManager.h"
#include "PlayerTopViewMove.h"
#include "PlayerBossStageMove.h"
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

	m_pMainCamera = Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA);

	if (m_pMainCamera == nullptr)
	{
		assert(L"�� ���� ���� ī�޶� ��ã�ڴٰ� ����");
	}

	//m_pMainCamera->SetPosition(0.f, 100.f, 0.f);
	//m_pMainCamera->SetRotation(0.f, 0.f, 0.f);
	//m_pMainCamera->GetTransform()->RotateX(90.f);

	m_pPlayer = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);
	if (m_pPlayer == nullptr)
	{
		assert(L"�÷��̾� �������� �������� ����;;");
	}



	//m_pPlayer->GetTransform()->position = Vector3(0, 0, -50);
	//m_pPlayer->GetTransform()->SetRotation(0, 0, 0);


	EnemyManager::GetInstance()->Boss_Spawn();



	//if (m_pPlayer == nullptr)
	//{
	//	assert(L"���� �������� �������� ����;;");
	//}

	// ==== UI ====
	UIWindowFactory::BossUI();
	m_bossui = false;
	// ==== UI ====

	m_bEnter = true;
}

void BossState::UpdateState()
{
	if (m_bEnter)
	{
		if (EnterProduce())
		{
			m_pPlayer->GetComponent<StateControl>()->SetState(L"playerBossMove");
			m_bEnter = false;
		}
	}



	DEBUG_LOG(L"Player Pos", m_pPlayer->GetTransform()->position);
	DEBUG_LOG(L"Camera Pos", m_pMainCamera->GetTransform()->position);
	//DEBUG_LOG(L"Camera Rot", m_pMainCamera->GetTransform()->rotation);
	DEBUG_LOG(L"Current Combat State : ", L"Boss State");
	m_fBossTime += dTime;
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
				//m_bPlayerSetting = false;
				m_bBossMove = true;
				vCameraOrigin = m_pMainCamera->GetTransform()->position;
				//vCameraRand = vCameraOrigin;
				m_pBoss = Core::GetInstance()->FindObjectByName(OBJECT_TAG_ENEMY, L"Boss");
			}
		}
	}

	//2. Camera shaking
	if (m_bCameraShaking)
	{
		m_pMainCamera->GetTransform()->position = RandForShaking() * fShakingForce + vCameraOrigin;
		fShakingTime -= dTime;


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

			m_pMainCamera->GetTransform()->position = Vector3( 0.f,0.f,-100.f);
			m_pPlayer->GetTransform()->position = Vector3(0.f, 0.f, -50.f);


			return true;
		}
	}
	return false;


	//4. Camera Moving
}

const Vector3 & BossState::RandForShaking()
{
	return vCameraRand = Vector3(rand() % 3 - 1.f, rand() % 3 - 1.f, rand() % 3 - 1.f);;
}

void BossState::CameraShaking()
{
}

void BossState::BossAppear()
{
}
