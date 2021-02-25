#include "stdafx.h"
#include "..\Include\RevolvesToTarget.h"

RevolvesToTarget::RevolvesToTarget(Desc * _desc)
{
	m_targetParent = _desc->targetParent;
	m_roationSpeed = _desc->roationSpeed;
	m_addingPos = _desc->addingPos;
	m_distanceLenght = _desc->distanceLenght;
	m_yOffSetDistance = _desc->yOffSetDistance;
}

RevolvesToTarget::~RevolvesToTarget()
{
}

void RevolvesToTarget::Initialize()
{
	assert(L"Please. Instert Target"  && m_targetParent);
	
	{
		m_target = INSTANTIATE(OBJECT_TAG_GARAGE_OBJECT);
		m_target->SetParents(m_targetParent);
		m_target->SetPosition(0, 0.f, -2.f);
		
		//m_target->SetRotation(-20.f, 0, 0.f);
		Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA)->SetParents(m_gameObject);
	}
	m_targetPos = m_target->GetTransform()->position;
}

void RevolvesToTarget::Update()
{
	// pos set
	Matrix temproyWorldMatrix = m_target->GetTransform()->GetWorldMatrix();
	Vector3 offSetY = Vector3(temproyWorldMatrix._21, temproyWorldMatrix._22, temproyWorldMatrix._23) * m_yOffSetDistance;
	m_targetPos = m_target->GetTransform()->position + ((-m_target->GetTransform()->GetForward()) * m_distanceLenght) + offSetY;

	//rotate set
	Quaternion rotY;
	rotY = m_target->GetTransform()->RotateAxis({0,1,0}, m_roationSpeed * dTime);
	m_lookDir = m_target->GetTransform()->rotation *= rotY;

	m_transform->position = m_targetPos;
	m_transform->rotation = m_lookDir;
}

void RevolvesToTarget::LateUpdate()
{
	// compute 
	DEBUG_LOG(L"Player Child Position", m_target->GetTransform()->position);
	DEBUG_LOG(L"Camera Position", (Vector3)m_transform->position);
	DEBUG_LOG(L"Camera Rotation", (Vector3)m_transform->rotation);
}

