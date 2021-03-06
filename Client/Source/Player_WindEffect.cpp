#include "stdafx.h"
#include "Player_WindEffect.h"

Player_WindEffect::Player_WindEffect(Desc * _desc)
{
	m_leftTrailPos = _desc->leftTrailPos;
	m_rightTrailPos = _desc->rightTrailPos;
	m_trailThick = _desc->trailThick;
}

void Player_WindEffect::Initialize()
{
	
	TrailRenderer::Desc trail;
	trail.trailCountPerSec = 45;
	auto leftEffect = INSTANTIATE()->AddComponent<TrailRenderer>(&trail);
	m_leftTrail = leftEffect->GetComponent<TrailRenderer>();

	auto rightEffect = INSTANTIATE()->AddComponent<TrailRenderer>(&trail);
	m_rightTrail = rightEffect->GetComponent<TrailRenderer>();

}

void Player_WindEffect::Update()
{
	Matrix world = m_transform->GetNoneScaleWorldMatrix();

	Vector3 pos1, pos2;
	D3DXVec3TransformCoord(&pos1, &m_leftTrailPos, &world);
	D3DXVec3TransformCoord(&pos2, &(m_leftTrailPos + Vector3(m_trailThick,0,0)), &world);
	m_leftTrail->RecordTrail(pos2, pos1);

	D3DXVec3TransformCoord(&pos1, &m_rightTrailPos, &world);
	D3DXVec3TransformCoord(&pos2, &(m_rightTrailPos - Vector3(m_trailThick, 0, 0)), &world);
	m_rightTrail->RecordTrail(pos2, pos1);
	
}
