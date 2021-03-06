#include "stdafx.h"
#include "..\Include\FieldCameraNearEnemyState.h"
#include "EnemyManager.h"
#include "FieldCameraInfo.h"


FieldCameraNearEnemyState::FieldCameraNearEnemyState()
{
}


FieldCameraNearEnemyState::~FieldCameraNearEnemyState()
{
}

void FieldCameraNearEnemyState::Initialize()
{
}

void FieldCameraNearEnemyState::EnterState()
{

	m_FieldCam = GetComponent<FieldCameraInfo>();
	/*m_FieldCam->SetTarget(m_gameObject->GetTransform());*/
	GameObject* player = PlayerInfoManager::GetInstance()->GetPlayer();
	m_NearObject = EnemyManager::GetInstance()->NearFindEenemy(player)->GetTransform();


	m_rotValue = 1.5f;
	m_minRandom = 2;
	m_maxRandom = 5;
	//

	m_FieldCam->SetAxisTargetPos(m_NearObject->GetWorldPosition() + Vector3(0.f, 0.f, 2.f));
	m_FieldCam->SetXMyAngle(0.f);
	m_FieldCam->SetYMyAngle(0.f);
	m_FieldCam->SetZMyAngle(0.f);


	m_FieldCam->SetXAxisAngle(20.f);
	m_FieldCam->SetYAxisAngle(180.f);
	m_FieldCam->SetZAxisAngle(0);

	m_FieldCam->RotateXAxisAngle(0.f);
	m_FieldCam->RotateYAxisAngle(0.f);


	m_FieldCam->SetDistance(20);
	m_FieldCam->SetFollowSpeed(3.f);
	m_FieldCam->SetRotateSpeed(1.f);
	m_FieldCam->SetLookSpeed(1.f);

	m_randomTimer = rand() % (m_maxRandom + 1 - m_minRandom) + m_minRandom;


	m_shakingX = rand() % (4 + 1 - 2) + 2;
	m_shakingY = rand() % (4 + 1 - 2) + 2;
	m_ShakingPosition = Vector3(m_shakingX, m_shakingY, 0.f);
}

void FieldCameraNearEnemyState::UpdateState()
{
	//
	m_culTime += dTime;
	//
	m_FieldCam->SetAxisTargetPos(m_NearObject->GetWorldPosition() + Vector3(0.f, 1.f, 2.f));
	//m_FieldCam->AddZAxisAngle()
	//m_FieldCam->AddZAxisAngle(1.5f *dTime);
	m_FieldCam->AddZAxisAngle(m_rotValue *dTime * 2.f);

	if (m_culTime > m_randomTimer)
	{
	
		m_rotValue *= -1;
		m_culTime = 0.f;
		m_randomTimer = rand() % (m_maxRandom + 1 - m_minRandom) + m_minRandom;

		DEBUG_LOG(L"+min", L"1");
	}


	

	DEBUG_LOG(L"Random", m_culTime);
	//m_FieldCam->AddZAxisAngle(-1.5f *dTime);

}

void FieldCameraNearEnemyState::ExitState()
{
}
