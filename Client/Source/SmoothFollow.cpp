#include "stdafx.h"
#include "..\Include\SmoothFollow.h"
#include "PlayerInfoManager.h"
#include "FieldCameraInfo.h"
SmoothFollow::SmoothFollow(Desc * _desc)
{
	m_toTarget = _desc->toTarget; //Player
	
	m_culDistance = _desc->culDistance;
	m_minDistance = _desc->minDistance;
	m_maxDistance = _desc->maxDistance;
	
	m_followMoveSpeed = _desc->followMoveSpeed;
	m_followRotationSpeed = _desc->followRotationSpeed;
	m_Damping = _desc->ratioDamping;

	m_offSet = _desc->offSetY;
}

SmoothFollow::~SmoothFollow()
{

}

void SmoothFollow::OnDisable()
{
	m_gameObject->GetComponent<FieldCameraInfo>()->Reset();

}

void SmoothFollow::OnEnable()
{
	//m_transform->rotation = { 0,0,0,1 };
	//m_transform->GetParents()->rotation = { 0,0,0,1 };
	m_gameObject->GetComponent<FieldCameraInfo>()->Reset();
}

void SmoothFollow::Initialize()
{
	assert(L"Please Set Target!" && m_toTarget);
	m_playerInfo = PlayerInfoManager::GetInstance();

	m_fromObject =  Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA);
	
	// 누군가를 부모로 사용하고싶을때
	//	m_fromObject->SetParents(m_gameObject);
	m_lookDirection = m_toTarget->GetTransform()->rotation;
}

void SmoothFollow::Update()
{
	
	DEBUG_LOG(L"따라가기", L"dd");
}

void SmoothFollow::LateUpdate()
{
	Matrix temproyWorldMatrix = m_toTarget->GetTransform()->GetWorldMatrix();
	Vector3 offSetY = Vector3(temproyWorldMatrix._21, temproyWorldMatrix._22, temproyWorldMatrix._23) * (m_culDistance);


	m_followDirection = Nalmak_Math::Lerp(m_followDirection, -m_toTarget->GetTransform()->GetForward() , dTime * 1.5f);
	m_lookDirection = Nalmak_Math::Lerp(m_lookDirection, m_toTarget->GetTransform()->rotation, dTime * 6.f);


	float Ratio = (m_playerInfo->GetSpeed() - m_playerInfo->GetMinSpeed()) / (m_playerInfo->GetMaxSpeed() - m_playerInfo->GetMinSpeed());
	float Interval = Nalmak_Math::Lerp(m_playerInfo->GetMinSpeed(), m_playerInfo->GetMaxSpeed(), Ratio);

	m_followDirection = Nalmak_Math::Normalize(m_followDirection);
	Vector3 targetPos = (m_toTarget->GetTransform()->position) + m_followDirection * (Interval + m_culDistance);

	
	m_transform->position = Nalmak_Math::Lerp(m_transform->position, targetPos + offSetY, dTime * 3.f);
	m_transform->rotation = m_lookDirection;



	DEBUG_LOG(L"Ratio", Ratio);
	DEBUG_LOG(L"Damping", m_playerInfo->GetSpeed());


}
