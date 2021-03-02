#include "stdafx.h"
#include "..\Include\SmallCannon.h"

#include "BulletDirMove.h"
#include "BulletEffect_StretchBillboard.h"
SmallCannon::SmallCannon(const ITEMINFO & copy) :PlayerItem(copy)
{
}

SmallCannon::~SmallCannon()
{
}

void SmallCannon::ItemShot()
{
	Matrix worldMat = m_bullet->GetTransform()->GetWorldMatrix();


	m_bullet->GetTransform()->position = Vector3(worldMat._41, worldMat._42, worldMat._43) + Vector3(worldMat._31, worldMat._32, worldMat._33) * 2;
	m_bullet->GetTransform()->DeleteParent();

	BulletEffect_StretchBillboard::Desc bulletinfo;
	bulletinfo.lifeTime = 5.f;
	bulletinfo.speed = 150.f;	
	bulletinfo.stretchRatio = 18.f;
	m_bullet->AddComponent<BulletEffect_StretchBillboard>(&bulletinfo);
	m_bullet = nullptr;
}

void SmallCannon::CreateBullet()
{
	if (m_bullet)
		return;


	VIBufferRenderer::Desc meshInfo;
	meshInfo.meshName = L"quadNoneNormal";
	meshInfo.mtrlName = L"fx_20mmCannon";
	// 2. BULLET INFO
	
	m_parents = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);

	m_bullet = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"cannon");
	m_bullet->AddComponent<VIBufferRenderer>(&meshInfo);
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
