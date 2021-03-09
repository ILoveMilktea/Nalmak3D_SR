#include "stdafx.h"
#include "..\Include\SmoothFollow.h"
#include "PlayerInfoManager.h"
#include "FieldCameraInfo.h"
#include "PlayerMove.h"

SmoothFollow::SmoothFollow(Desc * _desc)
{
	m_playerMoveInfo = _desc->toTarget->GetComponent<StateControl>()->GetState<PlayerMove>(L"playerMove"); //Player
	m_player = _desc->toTarget->GetTransform();

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
	//assert(L"Please Set Target!" && m_toTarget);
	//m_playerInfo = PlayerInfoManager::GetInstance();
	//m_fromObject =  Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA);
	//m_fromObject->SetParents(m_gameObject);
	//m_lookDirection = m_toTarget->GetTransform()->rotation;

	assert(L"Please Set Target!" && m_playerMoveInfo);
	m_fromObject =  Core::GetInstance()->FindObjectByName(OBJECT_TAG_CAMERA, L"mainCamera");
	m_playerInfo = PlayerInfoManager::GetInstance();

	m_lookDirection = m_player->rotation;
}

void SmoothFollow::Update()
{

	//DEBUG_LOG(L"NOOOOOO", L"dd");
}

void SmoothFollow::LateUpdate()
{
	Matrix temproyWorldMatrix = m_player->GetWorldMatrix();

	Vector3 offSetY = Vector3(temproyWorldMatrix._21, temproyWorldMatrix._22, temproyWorldMatrix._23);

	m_followDirection = Nalmak_Math::Lerp(m_followDirection, -m_player->GetForward() , dTime * 1.5f);
	m_followDirection = Nalmak_Math::Normalize(m_followDirection);

	m_lookDirection = Nalmak_Math::Lerp(m_lookDirection, m_player->rotation, dTime * 2.f);

	

	float Ratio = (m_playerInfo->GetSpeed() - m_playerInfo->GetMinSpeed()) / (m_playerInfo->GetMaxSpeed() - m_playerInfo->GetMinSpeed());

	//float Interval = Nalmak_Math::Lerp(m_playerInfo->GetMinSpeed(), m_playerInfo->GetMaxSpeed(), Ratio);

	//m_followDirection = Nalmak_Math::Normalize(m_followDirection);
	//Vector3 targetPos = (m_toTarget->GetTransform()->position) + m_followDirection * (Interval + m_culDistance);


	Vector3 targetPos = (m_player->position) + m_followDirection * (Ratio * 2 + 6) + Vector3(0, 1.7f, 0);

	m_transform->position = Nalmak_Math::Lerp(m_transform->position, targetPos, dTime * 4.f);
	m_transform->SetRotation(m_playerMoveInfo->GetRotXAngle(), m_playerMoveInfo->GetRotYAngle(),0);





}
