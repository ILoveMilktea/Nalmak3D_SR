#include "stdafx.h"
#include "PlayerEscapeState.h"
#include "PlayerSkillActor.h"
#include "PlayerItem.h"
#include "ScaleDampingDeffender.h"
#include "MouseOption.h"
#include "PlayerInfoManager.h"



PlayerEscapeState::PlayerEscapeState()
{
}


PlayerEscapeState::~PlayerEscapeState()
{
}

void PlayerEscapeState::Initialize()
{
	{
		m_playerInfo = PlayerInfoManager::GetInstance();
		m_inputManager = InputManager::GetInstance();
	}

}

void PlayerEscapeState::EnterState()
{


	m_skillActor = m_gameObject->GetComponent<PlayerSkillActor>();
	m_skillInfo = m_skillActor->GetSkillInfo();

	// test skill;
	// test defender skill; 
	m_dealy = m_skillInfo->GetItmeInfo().delay;

	{
		VIBufferRenderer::Desc meshInfo;
		//meshInfo.mtrlName = L"debugCollider";
		meshInfo.mtrlName = L"default_red";
		meshInfo.meshName  = L"sphere";

		ScaleDampingDeffender::Desc scaleDamping;
		scaleDamping.dampingSpeed = 3.f;
		scaleDamping.maximumScale = 15.0f;
		scaleDamping.axisDir = Vector3(0.f, 1.f, 0.f);
		
		SphereCollider::Desc sphereColliderInfo;
		sphereColliderInfo.collisionLayer = COLLISION_LAYER_SHIELD;
		sphereColliderInfo.radius = 1.f;

		auto shield = INSTANTIATE( OBJECT_TAG_PLAYER_SHIELD , L"playerNormalShield")->
			AddComponent<VIBufferRenderer>(&meshInfo)->
			AddComponent<ScaleDampingDeffender>(&scaleDamping)->
			AddComponent<SphereCollider>(&sphereColliderInfo);
		shield->SetParents(m_gameObject);
	}
	
}

void PlayerEscapeState::UpdateState()
{
	//float speed = 0;
	//D3DXVec2Normalize(&m_mouse->GetMouseMoveDir(), &m_mouse->GetMouseMoveDir());
	//if (m_inputManager->GetKeyPress(KEY_STATE_D))
	//	m_playerInfo->SetRollAngle(-15.f);
	//else if (m_inputManager->GetKeyPress(KEY_STATE_A))
	//	m_playerInfo->SetRollAngle(15.f);
	//else
	//	m_playerInfo->SetRollAngle(0.f);

	//float dirY = m_mouse->GetMouseMoveDir().x;
	//float dirX = m_mouse->GetMouseMoveDir().y;

	//float sensitive = m_playerInfo->GetDirSenser();
	//dirX = Nalmak_Math::Clamp(dirX, -sensitive, +sensitive);
	//dirY = Nalmak_Math::Clamp(dirY, -sensitive, +sensitive);


	//Quaternion quaterRotX, quaterRotY, quaterRotZ;
	//D3DXQuaternionRotationAxis(&quaterRotY, &m_transform->GetUp(), dirY * dTime * 1.5f);
	//D3DXQuaternionRotationAxis(&quaterRotX, &m_transform->GetRight(), dirX * dTime* 1.5f);
	//D3DXQuaternionRotationAxis(&quaterRotZ, &m_transform->GetForward(), m_playerInfo->GetRollAngle() * dTime * 0.1f);
	//m_transform->rotation *= (quaterRotX * quaterRotY * quaterRotZ);

	////1. 공기저항
	//speed -= 3.f;

	//if (m_inputManager->GetKeyPress(KEY_STATE_W))
	//	m_accel = Nalmak_Math::Lerp(m_accel, 1.f, dTime * 50);
	//else
	//	m_accel = Nalmak_Math::Lerp(m_accel, 0.f, dTime * 10);

	//m_accel = Nalmak_Math::Clamp(m_accel, 0.f, 1.f);
	//speed += m_accel * 5;


	//m_playerInfo->AddSpeed(speed);
	//m_transform->position += m_transform->GetForward() * m_playerInfo->GetSpeed() * dTime;

	//if (nullptr == Core::GetInstance()->FindObjectByName(OBJECT_TAG_PLAYER_SHIELD, L"playerNormalShield"))
	//	m_stateControl->SetState(L"playerMove");
}

void PlayerEscapeState::ExitState()
{
}
