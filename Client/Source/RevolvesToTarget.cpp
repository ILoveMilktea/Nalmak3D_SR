#include "stdafx.h"
#include "..\Include\RevolvesToTarget.h"

RevolvesToTarget::RevolvesToTarget(Desc * _desc)
{
	m_target = _desc->target;
	m_roationSpeed = _desc->roationSpeed;
	m_addingPos = _desc->addingPos;
	m_distanceLenght = _desc->distanceLenght;

}

RevolvesToTarget::~RevolvesToTarget()
{
}

void RevolvesToTarget::Initialize()
{
	assert(L"Please. Instert Target"  && m_target);
	
	m_target = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);
	////  카메라 객체를 자식으로..
	Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA)->SetParents(m_gameObject);

	m_distanceLenght = 120.f;
}

void RevolvesToTarget::Update()
{
	/*D3DXQuaternionRotationAxis();*/
	/*Quaternion rot;
	D3DXQuaternionRotationAxis(&rot, &_axis, _angle);
	return rot;*/

	//  1. toTarget;
	

	Quaternion quaterRotY;
	D3DXQuaternionRotationAxis(&quaterRotY, &m_transform->GetUp(), m_roationSpeed * dTime * 0.15f);
	//Vector3 targetPos;
	
	//m_transform->position  
	//m_transform->rotation *= quaterRotY;
	DEBUG_LOG(L"Camera Position", (Vector3)m_transform->position);
	DEBUG_LOG(L"Camera Rotation" , (Vector3)m_transform->rotation);
}

void RevolvesToTarget::LateUpdate()
{
}
