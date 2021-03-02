#include "stdafx.h"
#include "..\Include\AimMissile.h"

#include "BulletDirMove.h"


AimMissile::AimMissile(const ITEMINFO & _copy) 
	: PlayerItem(_copy)
{
}

AimMissile::~AimMissile()
{
}

void AimMissile::ItemShot()
{
	m_bullet[0]->GetTransform()->position = m_bullet[0]->GetTransform()->GetWorldPosition();
	m_bullet[0]->GetTransform()->DeleteParent();


	m_bullet[1]->GetTransform()->position = m_bullet[1]->GetTransform()->GetWorldPosition();
	m_bullet[1]->GetTransform()->DeleteParent();

	BulletDirMove::Desc bulletinfo;
	bulletinfo.speed = m_itemInfo.weaponSpeed;



	m_bullet[0]->AddComponent<BulletDirMove>(&bulletinfo);
	m_bullet[1]->AddComponent<BulletDirMove>(&bulletinfo);
	m_bullet[0] = nullptr;
	m_bullet[1] = nullptr;
}


void AimMissile::CreateBullet()
{
	if (m_bullet[0] || m_bullet[1])
		return;

	// 1. RENDER
	VIBufferRenderer::Desc meshInfo;
	meshInfo.meshName = L"sphere";
	meshInfo.mtrlName = L"default";
	// 2. BULLET INFO
  
	// 에임미사일은 단독 클래스 잖아 슛하고 크레이트만 해주는 
	m_parents = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);


	m_bullet[0] = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"Left");
	m_bullet[0]->AddComponent<VIBufferRenderer>(&meshInfo);
	m_bullet[0]->SetParents(m_parents);
	m_bullet[0]->SetPosition(-3.f, 0.f, 0.f);

	m_bullet[1] = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"Right");
	m_bullet[1]->AddComponent<VIBufferRenderer>(&meshInfo);
	m_bullet[1]->SetParents(m_parents);
	m_bullet[1]->SetPosition(3.f, 0.f, 0.f);



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


