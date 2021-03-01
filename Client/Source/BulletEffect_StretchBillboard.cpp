#include "stdafx.h"
#include "..\Include\BulletEffect_StretchBillboard.h"




BulletEffect_StretchBillboard::BulletEffect_StretchBillboard(Desc * _desc)
{
	m_lifeTime = _desc->lifeTime;
	m_speed = _desc->speed;
	m_stretchRatio = _desc->stretchRatio;
	m_dir = _desc->direction;
}

BulletEffect_StretchBillboard::~BulletEffect_StretchBillboard()
{
}

void BulletEffect_StretchBillboard::Initialize()
{
	m_camera = Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA)->GetComponent<Camera>();
	 auto player = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);
	m_dir = player->GetTransform()->GetForward();

	m_transform->SetScale(Vector3(1, m_stretchRatio, 1));

}

void BulletEffect_StretchBillboard::Update()
{
	if (m_lifeTime < 0)
	{
		DESTROY(m_gameObject);
		return;
	}
	m_lifeTime -= dTime;


	float angle = Nalmak_Math::Dot(Vector3(0, 1, 0), m_dir);

	Vector3 axis;
	D3DXVec3Cross(&axis, &Vector3(0, 1, 0), &m_dir);
	D3DXQuaternionRotationAxis(&m_transform->rotation, &axis, acos(angle));
	//m_transform->SetRotation(90,0,0);

	m_transform->position += m_dir * m_speed * dTime;

	

}


