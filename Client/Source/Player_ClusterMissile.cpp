#include "stdafx.h"
#include "..\Include\Player_ClusterMissile.h"
#include "ClusterBulletMove.h"
#include "PlayerInfoManager.h"

#include "ParticleRenderer.h"
#include "ParticleDead_IfCount0.h"

Player_ClusterMissile::Player_ClusterMissile(const ITEMINFO & copy)
	:PlayerItem(copy)
{

}

Player_ClusterMissile::~Player_ClusterMissile()
{
}

void Player_ClusterMissile::ItemShot()
{
	//effect Start!

	ParticleRenderer::Desc render;
	render.particleDataName = L"missile_smokeLaunch";
	auto obj = INSTANTIATE()->AddComponent<ParticleRenderer>(&render)->AddComponent<ParticleDead_IfCount0>();
	obj->GetComponent<ParticleRenderer>()->Play();
	obj->SetParents(m_bullet);

	//colision;
	SphereCollider::Desc sphereColInfo;
	sphereColInfo.collisionLayer = COLLISION_LAYER_BULLET_PLAYER;

	m_bullet->GetTransform()->DeleteParent();
	ClusterBulletMove::Desc bulletinfo;
	bulletinfo.speed = m_itemInfo.weaponSpeed;
	bulletinfo.accAngle = bulletinfo.speed;

	m_bullet->AddComponent<ClusterBulletMove>(&bulletinfo);
	m_bullet->AddComponent<SphereCollider>(&sphereColInfo);

	m_bullet = nullptr;

}

void Player_ClusterMissile::CreateBullet()
{
	if (m_bullet)
		return;
	m_parents = PlayerInfoManager::GetInstance()->GetPlayer();

	MeshRenderer::Desc meshInfo;
	meshInfo.meshName = m_itemInfo.modelName;
	meshInfo.mtrlName = L"su34";

	m_bullet = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"cluster");
	m_bullet->AddComponent<MeshRenderer>(&meshInfo);
	m_bullet->SetParents(m_parents);
	m_bullet->SetPosition(m_itemInfo.createPos);
	m_bullet->SetScale(0.2f, 0.2f, 0.2f);


}

void Player_ClusterMissile::DeleteBullet()
{
	if (m_bullet)
	{
		DESTROY(m_bullet);
		m_bullet = nullptr;
	}
}
