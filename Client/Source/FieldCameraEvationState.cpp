#include "stdafx.h"
#include "FieldCameraEvationState.h"

#include "FieldCameraInfo.h"

FieldCameraEvationState::FieldCameraEvationState()
{
}


FieldCameraEvationState::~FieldCameraEvationState()
{
}

void FieldCameraEvationState::Initialize()
{
}

void FieldCameraEvationState::EnterState()
{
	m_FieldCam = GetComponent<FieldCameraInfo>();
	m_gameObject->GetComponent<FieldCameraInfo>()->SetActive(false);
}

void FieldCameraEvationState::UpdateState()
{

}

void FieldCameraEvationState::ExitState()
{
}
