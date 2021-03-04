#include "stdafx.h"
#include "..\Include\FieldCameraZoomInState.h"


FieldCameraZoomInState::FieldCameraZoomInState()
{
	m_distance = 25.f;
}


FieldCameraZoomInState::~FieldCameraZoomInState()
{
}

void FieldCameraZoomInState::Initialize()
{
	m_lookAtTarget = PlayerInfoManager::GetInstance()->GetPlayer();

	

}

void FieldCameraZoomInState::EnterState()
{
	
	
}

void FieldCameraZoomInState::UpdateState()
{
	Matrix WorldMatrix = m_lookAtTarget->GetTransform()->GetWorldMatrix();
	Vector3 offSetY = Vector3(WorldMatrix._21, WorldMatrix._22, WorldMatrix._23) * (m_distance);

	m_fromPos = m_lookAtTarget->GetTransform()->position + offSetY;
	m_camDir = Nalmak_Math::Direction(m_fromPos, m_lookAtTarget->GetTransform()->position);
	m_transform->position = Nalmak_Math::Lerp(m_transform->position, m_fromPos, dTime);
	m_transform->LookAt(m_camDir + m_transform->position, 1.f);
}

void FieldCameraZoomInState::ExitState()
{
}
