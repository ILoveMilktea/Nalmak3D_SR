#include "stdafx.h"
#include "..\Include\Shooter.h"


Shooter::Shooter(Desc * _desc)
{
	m_eMovePattern = _desc->eMovePattern;
	m_firePos = _desc->firePos;
	m_speed = _desc->speed;
}

Shooter::~Shooter()
{
}

void Shooter::Initialize()
{
	// 플레이어가 바라보는 방향이 디렉션, 
	m_speed *= 2.f;
	m_core = Core::GetInstance();

	// 플레이어의 트랜스폼
	m_targetTransform = m_core->FindFirstObject(OBJECT_TAG_PLAYER)->GetTransform();
	m_transform->rotation = (m_targetTransform->rotation);
}

void Shooter::Update()
{
	if (m_fire)
	{
		m_fireDirection = m_targetTransform->GetForward();
		m_transform->position += m_fireDirection * m_speed * dTime;
	}
	else
	{
		Matrix temproyWorldMatrix = m_targetTransform->GetWorldMatrix();
		Vector3 offSetX = Vector3(temproyWorldMatrix._11, temproyWorldMatrix._12, temproyWorldMatrix._13) *  (m_firePos.x);
		Vector3 offSetY = Vector3(temproyWorldMatrix._21, temproyWorldMatrix._22, temproyWorldMatrix._23) *  (m_firePos.y);
		Vector3 offSetZ= Vector3(temproyWorldMatrix._31, temproyWorldMatrix._32, temproyWorldMatrix._33)  *  (m_firePos.z);

		//  m_desiredPos = (m_targetTransform->position + m_firePos) * offSet ;
		m_desiredPos = (m_targetTransform->GetTransform()->position) + (offSetX + offSetY + offSetZ) * 10.f;


		m_transform->SetPosition(m_desiredPos);
		m_transform->rotation = (m_targetTransform->rotation);
	}
}

void Shooter::ShooterActive(bool _activeCheck)
{
	//m_gameObject->GetTransform()->DeleteParent();
 	m_fire = _activeCheck;
}
