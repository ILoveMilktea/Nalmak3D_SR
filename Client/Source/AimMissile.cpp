#include "stdafx.h"
#include "..\Include\AimMissile.h"

#include "BulletDirMove.h"
#include "Player_AimMissile.h"
#include "DeadTimer.h"
AimMissile::AimMissile(const ITEMINFO & _copy) 
	: PlayerItem(_copy)
{
}

AimMissile::~AimMissile()
{
}

void AimMissile::ItemShot()
{
	SphereCollider::Desc missile_col;
	missile_col.radius = 1.f;
	missile_col.collisionLayer = COLLISION_LAYER_BULLET_PLAYER;
	m_bullet[0]->AddComponent<SphereCollider>(&missile_col);
	m_bullet[1]->AddComponent<SphereCollider>(&missile_col);

	m_bullet[0]->GetTransform()->DeleteParent();
	m_bullet[1]->GetTransform()->DeleteParent();

	Player_AimMissile::Desc bulletinfo;
	bulletinfo.speed = m_itemInfo.weaponSpeed;
	bulletinfo.deadTimer = 5.f;
	m_bullet[0]->AddComponent<Player_AimMissile>(&bulletinfo);
	m_bullet[1]->AddComponent<Player_AimMissile>(&bulletinfo);

	m_bullet[0] = nullptr;
	m_bullet[1] = nullptr;
}


void AimMissile::CreateBullet()
{
	if (m_bullet[0] || m_bullet[1])
		return;

	// 1. RENDER
	MeshRenderer::Desc meshInfo;
	meshInfo.meshName = m_itemInfo.modelName;
	meshInfo.mtrlName = L"kfir";
	// 2. BULLET INFO

	m_parents = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);


	m_bullet[0] = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"Left");
	m_bullet[0]->AddComponent<MeshRenderer>(&meshInfo);
	m_bullet[0]->SetParents(m_parents);
	m_bullet[0]->SetPosition({ m_itemInfo.createPos.x * -1.f, m_itemInfo.createPos.y,m_itemInfo.createPos.z});
	m_bullet[0]->SetScale(0.3f, 0.3f, 1.5f);

	m_bullet[1] = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"Right");
	m_bullet[1]->AddComponent<MeshRenderer>(&meshInfo);
	m_bullet[1]->SetParents(m_parents);
	m_bullet[1]->SetPosition(m_itemInfo.createPos);
	m_bullet[1]->SetScale(0.3f, 0.3f, 1.5f);


}

void AimMissile::DeleteBullet()
{
	for (int i = 0; i < 2; ++i)
	{
		if (m_bullet[i])
		{
			DESTROY(m_bullet[i]);
			m_bullet[i] = nullptr;
		}
	}
}


