#include "stdafx.h"
#include "..\Include\Player_AirTrailEffect.h"



Player_AirTrailEffect::Player_AirTrailEffect(Desc * _desc)
{
	m_interval = _desc->interval;
	m_thick = _desc->thick;
	m_offset = _desc->posOffset;
	m_lifeTime = _desc->lifeTime;
	m_isPlay = _desc->startOnPlay;
}

Player_AirTrailEffect::~Player_AirTrailEffect()
{
}

void Player_AirTrailEffect::Initialize()
{
	m_prePosition = m_transform->position;
	m_curPosition = m_transform->position;
}

void Player_AirTrailEffect::Update()
{
	m_curPosition = m_transform->position;

	if (m_isPlay)
		CreateMesh();

	m_prePosition = m_curPosition;
}

void Player_AirTrailEffect::CreateMesh()
{
	auto mesh = GameObject::Instantiate();
	MeshRenderer::Desc render;
	render.mtrl = m_material;
	//render.layer = RENDER_LAYER::RENDER_LAYER_EFFECT;
	/*ColorFadeDestroy::Desc color;
	color.startColor = m_color;
	color.endColor = Vector4(0, 0, 0, 0);
	color.lifeTime = m_lifeTime;*/
	mesh->AddComponent<MeshRenderer>(&render);// ->AddComponent<ColorFadeDestroy>(&color);

	mesh->GetTransform()->position = (m_curPosition + m_prePosition) * 0.5f + m_offset;
	mesh->GetTransform()->scale = Vector3(Nalmak_Math::Distance(m_curPosition, m_prePosition), m_thick, 0);

	Vector3 dir = Nalmak_Math::Normalize(m_prePosition - m_curPosition);
	float angle = acos(Nalmak_Math::Dot(dir, Vector3(1, 0, 0)));
	if (Nalmak_Math::Cross(dir, Vector3(1, 0, 0)).z > 0)
		angle *= -1.f;
	Quaternion quaternion;
	D3DXQuaternionRotationYawPitchRoll(&quaternion, 0, 0, angle);
	mesh->GetTransform()->rotation = quaternion;
}
