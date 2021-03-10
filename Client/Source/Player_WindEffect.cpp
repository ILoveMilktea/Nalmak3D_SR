#include "stdafx.h"
#include "Player_WindEffect.h"

Player_WindEffect::Player_WindEffect(Desc * _desc)
{
	m_leftTrailPos = _desc->leftTrailPos;
	m_rightTrailPos = _desc->rightTrailPos;
	m_trailThick = _desc->trailThick;
	m_trailTargetThick = _desc->trailThick;
	m_trailCurrentThick = _desc->trailThick;
}

void Player_WindEffect::Initialize()
{
	
	TrailRenderer::Desc trail;
	trail.trailCountPerSec = 5;
	AddComponent<TrailRenderer>(&trail);
	AddComponent<TrailRenderer>(&trail);

	auto comList = GetComponents<TrailRenderer>();
	m_leftTrail = comList[0];
	m_rightTrail = comList[1];

	m_timer = 1.f;
}

void Player_WindEffect::Release()
{
	DeleteComponent<TrailRenderer>();
	DeleteComponent<TrailRenderer>();
}

void Player_WindEffect::Update()
{
	m_timer -= dTime;

	if (m_timer < 0)
	{
		m_timer = Nalmak_Math::Rand(0.7f, 1.4f);
		m_trailTargetThick = Nalmak_Math::Rand(0.2f, 0.55f) * m_trailThick;
	}
	m_trailCurrentThick = Nalmak_Math::Lerp(m_trailCurrentThick, m_trailTargetThick, dTime * 2);

	Matrix world = m_transform->GetNoneScaleWorldMatrix();

	Vector3 pos1, pos2;
	D3DXVec3TransformCoord(&pos1, &(m_leftTrailPos - Vector3(m_trailCurrentThick, 0, 0)), &world);
	D3DXVec3TransformCoord(&pos2, &(m_leftTrailPos + Vector3(m_trailCurrentThick,0,0)), &world);
	m_leftTrail->RecordTrail(pos2, pos1);

	D3DXVec3TransformCoord(&pos1, &(m_rightTrailPos + Vector3(m_trailCurrentThick, 0, 0)), &world);
	D3DXVec3TransformCoord(&pos2, &(m_rightTrailPos - Vector3(m_trailCurrentThick, 0, 0)), &world);
	m_rightTrail->RecordTrail(pos2, pos1);
	
}
