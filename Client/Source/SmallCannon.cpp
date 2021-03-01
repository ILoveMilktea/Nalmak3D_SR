#include "stdafx.h"
#include "..\Include\SmallCannon.h"

#include "BulletDirMove.h"

SmallCannon::SmallCannon(const ITEMINFO & copy) :PlayerItem(copy)
{
}

SmallCannon::~SmallCannon()
{
}

void SmallCannon::ItemShot()
{

	m_bullet->GetTransform()->position = m_bullet->GetTransform()->GetWorldPosition();
	m_bullet->GetTransform()->DeleteParent();

	BulletDirMove::Desc bulletinfo;
	bulletinfo.speed = m_itemInfo.weaponSpeed;

	m_bullet->AddComponent<BulletDirMove>(&bulletinfo);
	m_bullet = nullptr;
}

void SmallCannon::CreateBullet()
{
	if (m_bullet)
		return;


	MeshRenderer::Desc meshInfo;
	meshInfo.meshName = L"sphere";
	meshInfo.mtrlName = L"default";
	// 2. BULLET INFO
	
	m_parents = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);

	m_bullet = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"cannon");
	m_bullet->AddComponent<MeshRenderer>(&meshInfo);
	m_bullet->SetParents(m_parents);
	m_bullet->SetPosition(0.f, 0.f, 0.f);

}

void SmallCannon::DeleteBullet()
{
	if (m_bullet)
	{
		DESTROY(m_bullet);
		m_bullet = nullptr;
	}
}
