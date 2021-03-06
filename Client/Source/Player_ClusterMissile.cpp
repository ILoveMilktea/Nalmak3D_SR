#include "stdafx.h"
#include "..\Include\Player_ClusterMissile.h"
#include "ClusterBulletMove.h"



Player_ClusterMissile::Player_ClusterMissile(const ITEMINFO & copy) 
	:PlayerItem(copy)
{

}

Player_ClusterMissile::~Player_ClusterMissile()
{
}

void Player_ClusterMissile::ItemShot()
{
	m_detector = Core::GetInstance()->FindObjectByName(OBJECT_TAG_UI, L"detector")->GetComponent<EnemyDetector>();

	if (m_detector == nullptr)
		return;

	auto lockonTarget = m_detector->GetLockOnTarget();

	if (lockonTarget == nullptr)
		return;




	m_bullet->GetTransform()->position = m_bullet->GetTransform()->GetWorldPosition();
	m_bullet->GetTransform()->DeleteParent();

	ClusterBulletMove::Desc bulletinfo;
	bulletinfo.speed = m_itemInfo.weaponSpeed;
	Vector2 screenPos = Core::GetInstance()->GetMainCamera()->WorldToScreenPos(lockonTarget->GetTransform()->position);


	bulletinfo.screenPos = Vector2(screenPos.x * cosf(D3DXToRadian(90.f)), screenPos.y * sinf(D3DXToRadian(90.f)));
	bulletinfo.target = lockonTarget;
	bulletinfo.accAngle = bulletinfo.speed;
	m_bullet->AddComponent<ClusterBulletMove>(&bulletinfo);

	m_bullet = nullptr;

}

void Player_ClusterMissile::CreateBullet()
{
	if (m_bullet)
		return;
	m_parents = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);

	VIBufferRenderer::Desc meshInfo;
	meshInfo.meshName = L"box";
	meshInfo.mtrlName = L"default";

	m_bullet = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"cluster");
	m_bullet->AddComponent<VIBufferRenderer>(&meshInfo);
	m_bullet->SetParents(m_parents);
	m_bullet->SetPosition(0.f, -1.f, 0.f);
}

void Player_ClusterMissile::DeleteBullet()
{
	if (m_bullet)
	{
		DESTROY(m_bullet);
		m_bullet= nullptr;
	}
}
