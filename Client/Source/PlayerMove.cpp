#include "stdafx.h"
#include "..\Include\PlayerMove.h"
#include "PlayerInfoManager.h"
#include "MouseOption.h"

#include "Enemy_Bullet_Manager.h"

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
	m_playerInfo->SetMaxSpeed(20.f);

	
	Vector3 eulerRot = m_transform->GetEulerRotation();
	m_playerInfo->GetAddRot().x = Deg2Rad * eulerRot.x;
	m_playerInfo->GetAddRot().y = Deg2Rad * eulerRot.y;
	m_playerInfo->GetAddRot().z = Deg2Rad * eulerRot.z;



}

void PlayerMove::EnterState()
{

}

void PlayerMove::UpdateState()
{
	float speed = 0;
	float xSensitive = 40.f;
	float ySensitive = 30.f;
	float zSensitive = 350.f;
	

	if (m_inputManager->GetKeyPress(KEY_STATE_D))
		m_rotZAngle -= dTime * 3.f;
	else if (m_inputManager->GetKeyPress(KEY_STATE_A))
		m_rotZAngle += dTime * 3.f;
	else
	{
		if (m_rotZAngle > 360)
		{
			m_rotZAngle -= (m_rotZAngle / 360) * 360;
		}
		else if (m_rotZAngle < -360)
		{
			m_rotZAngle += (1 + (abs(m_rotZAngle) / 360)) * 360;
		}

		if (m_rotZAngle < -180)
		{
			m_rotZAngle = Nalmak_Math::Lerp(m_rotZAngle, -360.f, dTime * 3);
		}
		else if (m_rotZAngle > 180)
		{
			m_rotZAngle = Nalmak_Math::Lerp(m_rotZAngle, 360.f, dTime * 3);
		}
		else
		{
			m_rotZAngle = Nalmak_Math::Lerp(m_rotZAngle, 0.f, dTime * 3);
		}


	}


	//m_rotZAngle = Nalmak_Math::Clamp(m_rotZAngle, -15.f, 15.f);

	Vector2 mouseDT = InputManager::GetInstance()->GetMouseScreenPos();
	mouseDT.x = Nalmak_Math::Clamp(mouseDT.x, WINCX * 0.25f, WINCX * 0.75f);
	mouseDT.y = Nalmak_Math::Clamp(mouseDT.y, WINCY * 0.25f, WINCY * 0.75f);
	mouseDT = mouseDT - Vector2(HALF_WINCX, HALF_WINCY);
	mouseDT.x /= (float)HALF_WINCX;
	mouseDT.y /= (float)HALF_WINCY;
	Vector2 normMouse = Nalmak_Math::Normalize(mouseDT);
	normMouse.x = min(mouseDT.x, normMouse.x);
	//rotaionByMouse.z = Nalmak_Math::Clamp(rotaionByMouse.z, -dTime * 30, dTime * 30);

	m_rotXAngle += mouseDT.y * ySensitive * dTime;
	m_rotYAngle += mouseDT.x * xSensitive * dTime;
	m_rotZAngle -= asinf(mouseDT.x) * 2.f / PI * zSensitive * dTime;

	/*m_rotZAngle -= mouseDT.x + zSensitive * dTime;
	m_rotZAngle = Nalmak_Math::Lerp(m_rotZAngle, 0.f, dTime * 4);*/


	m_transform->SetRotation(m_rotXAngle, m_rotYAngle, m_rotZAngle);

	 speed -= 3.f;

	if (m_inputManager->GetKeyPress(KEY_STATE_W))
		 m_accel = Nalmak_Math::Lerp(m_accel , 1.f, dTime * 10);
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

float PlayerMove::GetRotXAngle()
{
	return m_rotXAngle;
}

float PlayerMove::GetRotYAngle()
{
	return m_rotYAngle;
}

float PlayerMove::GetRotZAngle()
{
	return m_rotZAngle;
}
