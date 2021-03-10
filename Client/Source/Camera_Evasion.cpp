#include "stdafx.h"
#include "..\Include\Camera_Evasion.h"
#include "SmoothFollow.h"
#include "FieldCameraInfo.h"


Camera_Evasion::Camera_Evasion()
{
}


Camera_Evasion::~Camera_Evasion()
{
}

void Camera_Evasion::Initialize()
{
}

void Camera_Evasion::EnterState()
{
	m_gameObject->GetComponent<SmoothFollow>()->SetActive(false);
	m_gameObject->GetComponent<FieldCameraInfo>()->SetActive(false);
	//if u want setting MainCamera's real transform, must be Set false 'FieldCameraInfo' component

	m_transform->SetPosition(Vector3(0.f, 25.f, 0.f));
	m_transform->SetRotation(90.f, 0.f, 0.f);
}

void Camera_Evasion::UpdateState()
{

}

void Camera_Evasion::ExitState()
{
}
