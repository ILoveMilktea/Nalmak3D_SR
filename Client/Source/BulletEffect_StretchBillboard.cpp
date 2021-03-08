#include "stdafx.h"
#include "..\Include\BulletEffect_StretchBillboard.h"

#include "Enemy.h"

#include "ItemManager.h"
#include "PlayerItem.h"
#include "Enemy_Boss.h"
#include "ParticleDead_IfCount0.h"




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

	m_material = GetComponent<VIBufferRenderer>()->GetMaterial();

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

	Matrix view =  m_camera->GetViewMatrix();
	Matrix billboard;
	D3DXMatrixIdentity(&billboard);
	memcpy(&billboard.m[0][0], &view.m[0][0], sizeof(Vector3));
	memcpy(&billboard.m[1][0], &view.m[1][0], sizeof(Vector3));
	memcpy(&billboard.m[2][0], &view.m[2][0], sizeof(Vector3));

	D3DXMatrixInverse(&billboard, 0, &billboard);

	m_material->SetMatrix("g_invViewForBillboard", billboard);

}

void BulletEffect_StretchBillboard::OnTriggerEnter(Collisions & _collision)
{
	int iDmg = ItemManager::GetInstance()->FindItemObject(L"Weapon", L"Cannon")->GetItmeInfo().weaponAttak;

	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_ENEMY)
		{
			obj.GetGameObject()->GetComponent<Enemy>()->Damaged(iDmg);

			ParticleRenderer::Desc effectDesc;
			effectDesc.particleDataName = L"hit_effect_by_smallCannon";
			auto effect = INSTANTIATE()->AddComponent<ParticleRenderer>(&effectDesc)->AddComponent<ParticleDead_IfCount0>();
			effect->SetPosition(obj.GetGameObject()->GetTransform()->GetWorldPosition());

			DESTROY(m_gameObject);
		}

		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_BOSS)
		{
			obj.GetGameObject()->GetComponent<Boss>()->Damaged(iDmg);

			ParticleRenderer::Desc effectDesc;
			effectDesc.particleDataName = L"hit_effect_by_smallCannon";
			auto effect = INSTANTIATE()->AddComponent<ParticleRenderer>(&effectDesc)->AddComponent<ParticleDead_IfCount0>();
			effect->SetPosition(obj.GetGameObject()->GetTransform()->GetWorldPosition());

			DESTROY(m_gameObject);
		}
	}
}

void BulletEffect_StretchBillboard::OnTriggerStay(Collisions & _collision)
{
}

void BulletEffect_StretchBillboard::OnTriggerExit(Collisions & _collision)
{
}


