#include "stdafx.h"
#include "..\Include\Player_Weapon_Homing.h"

#include "HomingBulletMove.h"
#include "EnemyDetector.h"

Player_Weapon_Homing::Player_Weapon_Homing(const ITEMINFO & _copy)
	:PlayerItem(_copy)
{
	m_reloadTerm = 0.5f;

	m_time = TimeManager::GetInstance();
}

Player_Weapon_Homing::~Player_Weapon_Homing()
{
}

void Player_Weapon_Homing::ItemShot()
{
	m_detector = Core::GetInstance()->FindObjectByName(OBJECT_TAG_UI, L"detector")->GetComponent<EnemyDetector>();
	if (m_detector == nullptr)
		return;

	if (m_bullet.empty())
		return;

	auto lockonTarget = m_detector->GetLockOnTarget();
	
	if (lockonTarget == nullptr)
		return;

	auto bullet = m_bullet.front();

	bullet->GetTransform()->position = bullet->GetTransform()->GetWorldPosition();
	bullet->GetTransform()->DeleteParent();

	Rigidbody::Desc desc_rb;
	desc_rb.isGravity = false;
	desc_rb.isAirDrag = true;
	HomingBulletMove::Desc desc_hbm;
	desc_hbm.target = lockonTarget;
	//Vector2 screenPos = m_mainCamera->WorldToScreenPos(enemy->GetTransform()->position);


	//desc_hbm.winPos = 
	
	bullet->AddComponent<Rigidbody>(&desc_rb);
	bullet->AddComponent<HomingBulletMove>(&desc_hbm);

	m_bullet.erase(m_bullet.begin());
}

void Player_Weapon_Homing::CreateBullet()
{
	if (m_bullet.size() > 3)
		return;

	//m_reloadTimer += m_time->GetdeltaTime();

	//if (m_reloadTimer < m_reloadTerm)
	//	return;

	//m_reloadTimer = 0.f;

	// 1. RENDER
	VIBufferRenderer::Desc meshInfo;
	meshInfo.meshName = L"sphere";
	meshInfo.mtrlName = L"default";


	m_parents = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);

	auto bullet = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"Homing");
	bullet->AddComponent<VIBufferRenderer>(&meshInfo);
	bullet->SetParents(m_parents);
	bullet->SetPosition(0.f, -1.f, 0.f);
	Vector3 eulerRotate = m_parents->GetTransform()->GetEulerRotation();
	bullet->GetTransform()->SetRotation(eulerRotate.x, eulerRotate.y, eulerRotate.z);

	m_bullet.emplace_back(bullet);
}

void Player_Weapon_Homing::DeleteBullet()
{
	for (auto bullet : m_bullet)
	{
		DESTROY(bullet);
		bullet = nullptr;
	}

	m_bullet.clear();
}
