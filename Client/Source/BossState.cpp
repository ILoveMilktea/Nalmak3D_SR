#include "stdafx.h"
#include "..\Include\BossState.h"

#include "EnemyManager.h"
#include "PlayerTopViewMove.h"


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
		assert(L"아 ㅋㅋ 메인 카메라 못찾겠다고 ㅋㅋ");
	}

	//m_pMainCamera->SetPosition(0.f, 100.f, 0.f);
	//m_pMainCamera->SetRotation(0.f, 0.f, 0.f);
	//m_pMainCamera->GetTransform()->RotateX(90.f);

	m_pPlayer = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);
	if (m_pPlayer == nullptr)
	{
		assert(L"플레이어 못받은거 같은데여 ㅋㅋ;;");
	}
	m_pPlayer->DeleteComponent<PlayerTopViewMove>();

	//m_pPlayer->GetTransform()->position = Vector3(0, 0, -50);
	//m_pPlayer->GetTransform()->SetRotation(0, 0, 0);


	EnemyManager::GetInstance()->Boss_Spawn();



	//if (m_pPlayer == nullptr)
	//{
	//	assert(L"보스 못받은거 같은데여 ㅋㅋ;;");
	//}


	m_bEnter = true;
}

void BossState::UpdateState()
{
	if (m_bEnter)
	{
		EnterProduce();
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

void BossState::EnterProduce()
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
			if (m_pPlayer->GetTransform()->position == m_vPlayerInitPos)
			{
		
			}

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
	//if (fShakingTime <= 0)
	//{
	//	m_pMainCamera->GetTransform()->position = vCameraOrigin;
	//	m_bCameraShaking = false;
	//}

	if (m_bCameraShaking)
	{
		m_pMainCamera->GetTransform()->position = RandForShaking() * fShakingForce + vCameraOrigin;

		if (m_pBoss != nullptr)
		{
			//m_pPlayer->GetTransform()->position.z -= dTime * 10.f;
			//m_pMainCamera->GetTransform()->position.y = Nalmak_Math::Lerp(m_pMainCamera->GetTransform()->position.y, 0.f, dTime * 2);
			//m_pMainCamera->GetTransform()->position.z = Nalmak_Math::Lerp(m_pMainCamera->GetTransform()->position.z, -40.f, dTime * 2);
			//m_pMainCamera->GetTransform()->rotation.x *= dTime;
		}

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
			}
		}
	}

	if (m_bCameraProduce)
	{
		m_pMainCamera->GetTransform()->position.z 
			= Nalmak_Math::Lerp(m_pMainCamera->GetTransform()->position.z, 
				m_pPlayer->GetTransform()->position.z - 50.f, dTime);

		m_pMainCamera->GetTransform()->position.y
			= Nalmak_Math::Lerp(m_pMainCamera->GetTransform()->position.y,
				0.f, dTime);

		m_pMainCamera->GetTransform()->SetRotationX(0);
	}

	

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

