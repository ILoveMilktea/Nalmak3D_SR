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


	m_rotValue = 2;
	m_minRandom = 0;
	m_maxRandom = 2;
	//

	m_FieldCam->SetAxisTargetPos(m_NearObject->GetWorldPosition() + Vector3(0.f, 0.f, 2.f));
	m_FieldCam->SetXMyAngle(10.f);
	m_FieldCam->SetYMyAngle(0.f);
	m_FieldCam->SetZMyAngle(0.f);


	m_FieldCam->SetXAxisAngle(30.f);
	m_FieldCam->SetYAxisAngle(180.f);
	m_FieldCam->SetZAxisAngle(0);

	m_FieldCam->RotateXAxisAngle(0.f);
	m_FieldCam->RotateYAxisAngle(0.f);


	m_FieldCam->SetDistance(20);
	m_FieldCam->SetFollowSpeed(3.f);
	m_FieldCam->SetRotateSpeed(1.f);
	m_FieldCam->SetLookSpeed(1.f);

	m_randomTimer = rand() % (m_maxRandom + 1 - m_minRandom) + m_minRandom;


	m_shakingX = rand() % (4 + 1 - 0) + 0;
	m_shakingY = rand() % (4 + 1 - 0) + 0;
	m_shakingZ = rand() % (4 + 1 - 0) + 0;
	m_ShakingPosition = { 0,0,2 };

	m_minValue = -10.f;
	m_maxValue = 10.f;
}

void FieldCameraNearEnemyState::UpdateState()
{
	//
	m_culTime += dTime;
	//

	m_FieldCam->SetAxisTargetPos(m_NearObject->GetWorldPosition() + m_ShakingPosition);
	m_FieldCam->AddZAxisAngle(m_rotValue * dTime * 3.f , -10.f, 10.f);
	DEBUG_LOG(L"ASD",m_FieldCam->GetZAxisAngle());

	if (m_culTime > m_randomTimer)
	{
		m_shakingX = rand() % (2 + 1  +2)  -2;
		m_shakingY = rand() % (2 + 1 + 2) - 2;
		m_randomTimer = rand() % (m_maxRandom + 1 - m_minRandom) + m_minRandom;
		m_culTime = 0.f;
	}
	else
	{
		//m_shakingZ = rand() % (4 + 1 - 0) + 0;
		m_ShakingPosition = Nalmak_Math::Lerp(m_ShakingPosition, Vector3((float)m_shakingX, (float)m_shakingY, (float)m_shakingZ), dTime * 2.f);
	}


	if (m_FieldCam->GetZAxisAngle() > m_maxValue - 1.f)
	{
		m_rotValue = -1;
		return;
	}
	else if (m_FieldCam->GetZAxisAngle() < m_minValue + 1.f)
	{
		m_rotValue = 1;
		return;
	}

}

void FieldCameraNearEnemyState::ExitState()
{
}
