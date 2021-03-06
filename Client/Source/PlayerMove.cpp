#include "stdafx.h"
#include "..\Include\PlayerMove.h"
#include "PlayerInfoManager.h"
#include "MouseOption.h"

#include "Bullet_Manager.h"

PlayerMove::PlayerMove()
{
}


PlayerMove::~PlayerMove()
{
}

void PlayerMove::Initialize()
{
	m_inputManager = InputManager::GetInstance();
	m_playerInfo = PlayerInfoManager::GetInstance();
	m_timeMananger = TimeManager::GetInstance();
	m_playerInfo->SetSpeed(2);
	m_playerInfo->SetRollAngle(15.f);
	m_playerInfo->SetDirSeneser(0.5f);

	m_playerInfo->SetMinSpeed(0.f);
	m_playerInfo->SetMaxSpeed(22.f);


	
	Vector3 eulerRot = m_transform->GetEulerRotation();
	m_playerInfo->GetAddRot().x = Deg2Rad * eulerRot.x;
	m_playerInfo->GetAddRot().y = Deg2Rad * eulerRot.y;
	m_playerInfo->GetAddRot().z = Deg2Rad * eulerRot.z;
	m_mouse = GetComponent<MouseOption>();



}

void PlayerMove::EnterState()
{

}

void PlayerMove::UpdateState()
{
	float speed = 0;
	D3DXVec2Normalize(&m_mouse->GetMouseMoveDir(), &m_mouse->GetMouseMoveDir());
	if (m_inputManager->GetKeyPress(KEY_STATE_D))
		m_playerInfo->SetRollAngle(-15.f);
	else if (m_inputManager->GetKeyPress(KEY_STATE_A))
		m_playerInfo->SetRollAngle(15.f);
	else
		m_playerInfo->SetRollAngle(0.f);

	float dirY = m_mouse->GetMouseMoveDir().x;
	float dirX = m_mouse->GetMouseMoveDir().y;

	float sensitive = m_playerInfo->GetDirSenser();
	dirX = Nalmak_Math::Clamp(dirX, -sensitive, +sensitive);
	dirY = Nalmak_Math::Clamp(dirY, -sensitive, +sensitive);

	
	Quaternion quaterRotX , quaterRotY, quaterRotZ;
	D3DXQuaternionRotationAxis(&quaterRotY, &m_transform->GetUp(), dirY * dTime * 1.5f);
	D3DXQuaternionRotationAxis(&quaterRotX, &m_transform->GetRight(), dirX * dTime* 1.5f);
	D3DXQuaternionRotationAxis(&quaterRotZ, &m_transform->GetForward(), m_playerInfo->GetRollAngle() * dTime * 0.1f);
	m_transform->rotation *=  (quaterRotX * quaterRotY * quaterRotZ);
	
	//1. 공기저항
	 speed -= 3.f;

	 if (m_inputManager->GetKeyPress(KEY_STATE_W))
		 m_accel = Nalmak_Math::Lerp(m_accel , 1.f, dTime * 50);
	else
		m_accel = Nalmak_Math::Lerp(m_accel, 0.f, dTime * 10);

	m_accel = Nalmak_Math::Clamp(m_accel, 0.f, 1.f);
	speed += m_accel * 5;
	

	m_playerInfo->AddSpeed(speed);
	m_transform->position += m_transform->GetForward() * m_playerInfo->GetSpeed() * dTime;



}

void PlayerMove::ExitState()
{
}



Quaternion* PlayerMove::Rotation(const Vector3 & _dir)
{
	Quaternion rot;
										// 마우스의 x증감량
	m_playerInfo->GetAddRot().y += D3DXToRadian(_dir.x) * m_playerInfo->GetDirSenser() * dTime;
	m_playerInfo->GetAddRot().x += D3DXToRadian(_dir.y) * m_playerInfo->GetDirSenser() * dTime;

	return D3DXQuaternionRotationYawPitchRoll(&rot, m_playerInfo->GetAddRot().y, m_playerInfo->GetAddRot().x, m_playerInfo->GetAddRot().z);
}
