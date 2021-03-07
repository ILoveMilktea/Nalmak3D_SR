#include "stdafx.h"
#include "..\Include\Camera_Boss_Appear.h"
#include "EnemyManager.h"
#include "FieldCameraInfo.h"


Camera_Boss_Appear::Camera_Boss_Appear()
{
}


Camera_Boss_Appear::~Camera_Boss_Appear()
{
}

void Camera_Boss_Appear::Initialize()
{
}

void Camera_Boss_Appear::EnterState()
{
	//m_pMainCamera = Core::GetInstance()->GetMainCamera();
	m_pPlayer = PlayerInfoManager::GetInstance()->GetPlayer();

	assert(L"player can't Get at CameraBossAppear" && m_pPlayer);
}

void Camera_Boss_Appear::UpdateState()
{

	if (!m_bShaking & !m_bProduce && !m_bNext)
	{
		if (EnemyManager::GetInstance()->Get_Boss()->GetComponent<StateControl>()->GetCurStateString()
			== L"Boss_Enter")
		{
			m_bShaking = true;
			m_vCameraOrigin = m_transform->position;
		}
	}

	if (m_bShaking&& !m_bNext)
	{
		m_transform->position = RandForShaking() * m_fShakingForce + m_vCameraOrigin;

		if (EnemyManager::GetInstance()->Get_Boss()->GetComponent<StateControl>()->GetCurStateString()
			== L"Boss_Interrupt")
		{
			//카메라 연출로 들어가야함. 이 이전에는 카메라 쉐이킹만 주다가.
			m_bShaking = false;
			m_bProduce = true;
			//m_gameObject->GetComponent<FieldCameraInfo>()->SetActive(true);
			//m_gameObject->GetComponent<FieldCameraInfo>()->SetTarget(PlayerInfoManager::GetInstance()->GetPlayer()->GetTransform());
		
		}
	}

	if (m_bProduce && !m_bNext)
	{
		m_transform->GetTransform()->position.z
			= Nalmak_Math::Lerp(m_transform->GetTransform()->position.z,
				m_pPlayer->GetTransform()->position.z - 50.f, dTime);

		m_transform->GetTransform()->position.y
			= Nalmak_Math::Lerp(m_transform->GetTransform()->position.y,
				0.f, dTime);

		m_transform->GetTransform()->SetRotationX(0);

		if (m_transform->GetTransform()->position.y <= 0.2f)
		{
			m_gameObject->GetComponent<StateControl>()->SetState(L"CameraBoss");
			m_bNext = true;
		}
	}

	DEBUG_LOG(L"Camera Pos", m_transform->position);
}

void Camera_Boss_Appear::ExitState()
{
}

const Vector3& Camera_Boss_Appear::RandForShaking()
{
	return m_vCameraRand = Vector3(rand() % 3 - 1.f, rand() % 3 - 1.f, rand() % 3 - 1.f);
}
