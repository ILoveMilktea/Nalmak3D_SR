#include "stdafx.h"
#include "..\Include\MidBoss_SingleBullet.h"

#include "PlayerInfoManager.h"
#include "ItemManager.h"


MidBoss_SingleBullet::MidBoss_SingleBullet(Desc * _desc)
{
	m_lifeTime = _desc->lifeTime;
	m_speed = _desc->speed;
	m_stretchRatio = _desc->stretchRatio;
	m_dir = _desc->direction;

	m_dmg = _desc->dmg;
}

MidBoss_SingleBullet::~MidBoss_SingleBullet()
{
}

void MidBoss_SingleBullet::Initialize()
{
	m_camera = Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA)->GetComponent<Camera>();

	m_transform->SetScale(Vector3(1, m_stretchRatio *2.45f, 1) * 0.35f);

	m_material = GetComponent<VIBufferRenderer>()->GetMaterial();
}

void MidBoss_SingleBullet::Update()
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

	Matrix view = m_camera->GetViewMatrix();
	Matrix billboard;
	D3DXMatrixIdentity(&billboard);
	memcpy(&billboard.m[0][0], &view.m[0][0], sizeof(Vector3));
	memcpy(&billboard.m[1][0], &view.m[1][0], sizeof(Vector3));
	memcpy(&billboard.m[2][0], &view.m[2][0], sizeof(Vector3));

	D3DXMatrixInverse(&billboard, 0, &billboard);

	m_material->SetMatrix("g_invViewForBillboard", billboard);
}

void MidBoss_SingleBullet::OnTriggerEnter(Collisions & _collision)
{
	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_PLAYER)
		{
			PlayerInfoManager::GetInstance()->SetDamage((int)m_dmg);

			DESTROY(m_gameObject);
		}
	}
}

void MidBoss_SingleBullet::OnTriggerStay(Collisions & _collision)
{
}

void MidBoss_SingleBullet::OnTriggerExit(Collisions & _collision)
{
}
