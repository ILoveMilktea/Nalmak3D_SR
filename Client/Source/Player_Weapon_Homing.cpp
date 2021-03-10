#include "stdafx.h"
#include "..\Include\Player_Weapon_Homing.h"

#include "HomingBulletMove.h"
#include "EnemyDetector.h"
#include "UIFactory.h"

Player_Weapon_Homing::Player_Weapon_Homing(const ITEMINFO & _copy)
	:PlayerItem(_copy)
{
	m_reloadTerm = 0.5f;

	m_time = TimeManager::GetInstance();
	m_mode = MULTI;
}

Player_Weapon_Homing::~Player_Weapon_Homing()
{
}

void Player_Weapon_Homing::ItemShot()
{
	// object check 
	if (!Core::GetInstance()->FindObjectByName(OBJECT_TAG_UI, L"detector"))
		return;

	// detector check
	m_detector = Core::GetInstance()->FindObjectByName(OBJECT_TAG_UI, L"detector")->GetComponent<EnemyDetector>();
	if (m_detector == nullptr)
		return;

	// remain bullet check
	if (m_bullet.empty())
		return;

	auto lockonTarget = m_detector->GetLockOnTarget();
	
	// target at least 1 check
	if (lockonTarget == nullptr)
		return;

	int randMode = int(rand() % 2);

	switch (randMode)
	{
	case Player_Weapon_Homing::SINGLE:
	{
		auto bullet = m_bullet.front();

		//bullet->GetTransform()->position = bullet->GetTransform()->GetWorldPosition();
		bullet->GetTransform()->DeleteParent();

		Rigidbody::Desc desc_rb;
		desc_rb.isGravity = false;
		desc_rb.isAirDrag = true;
		desc_rb.dragCoefficient = 0.47f;
		HomingBulletMove::Desc desc_hbm;
		desc_hbm.target = lockonTarget;
		Vector2 screenPos = Core::GetInstance()->GetMainCamera()->WorldToScreenPos(lockonTarget->GetTransform()->position);

		desc_hbm.winPos = Vector3(screenPos.x, screenPos.y, 0.f);

		bullet->AddComponent<Rigidbody>(&desc_rb);
		bullet->AddComponent<HomingBulletMove>(&desc_hbm);

		SphereCollider::Desc single_col;
		single_col.collisionLayer = COLLISION_LAYER_BULLET_PLAYER;
		single_col.radius = 1.f;
		bullet->AddComponent<SphereCollider>(&single_col);


		m_bullet.erase(m_bullet.begin());
	}
		break;
	case Player_Weapon_Homing::MULTI:
	{
		GameObject* prevTarget = nullptr;
		auto target = m_detector->GetDetectedTargetList().begin();
		float radian = Deg2Rad * 90.f;

		for (auto bullet : m_bullet)
		{
			bullet->GetTransform()->position = bullet->GetTransform()->GetWorldPosition();
			bullet->GetTransform()->DeleteParent();

			Rigidbody::Desc desc_rb;
			desc_rb.isGravity = false;
			desc_rb.isAirDrag = true;
			desc_rb.dragCoefficient = 0.47f;
			HomingBulletMove::Desc desc_hbm;
			
			desc_hbm.target = *target;
			Vector2 screenPos = Core::GetInstance()->GetMainCamera()->WorldToScreenPos((*target)->GetTransform()->position);

			// check same target
			if (prevTarget == *target)
			{
				desc_hbm.winPos = Vector3(screenPos.x * cosf(radian), screenPos.y * sinf(radian), 0.f);
				radian += Deg2Rad * 90.f;
			}
			else
			{
				desc_hbm.winPos = Vector3(screenPos.x, screenPos.y, 0.f);
				radian = Deg2Rad * 90.f;
			}

			bullet->AddComponent<Rigidbody>(&desc_rb);
			bullet->AddComponent<HomingBulletMove>(&desc_hbm);
						
			// round list
			prevTarget = *target;
			++target;
			if (target == m_detector->GetDetectedTargetList().end())
				target = m_detector->GetDetectedTargetList().begin();

			SphereCollider::Desc multi_col;
			multi_col.collisionLayer = COLLISION_LAYER_BULLET_PLAYER;
			multi_col.radius = 1.f;
			bullet->AddComponent<SphereCollider>(&multi_col);
		}


		m_bullet.clear();
	}
		break;
	}
}

void Player_Weapon_Homing::CreateBullet()
{
	if (m_bullet.size() > 5)
		return;

	for (int i = 0; i < 4; ++i)
	{
		MeshRenderer::Desc meshInfo;
		meshInfo.meshName = m_itemInfo.modelName;
		meshInfo.mtrlName = L"su34";


		m_parents = PlayerInfoManager::GetInstance()->GetPlayer();

		auto bullet = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"Homing");
		bullet->AddComponent<MeshRenderer>(&meshInfo);
		bullet->SetParents(m_parents);
		bullet->SetPosition(m_itemInfo.createPos);
		bullet->SetScale(0.2f, 0.2f, 0.3f);
		//bullet->GetTransform()->SetRotation(eulerRotate.x, eulerRotate.y, eulerRotate.z);

		m_bullet.emplace_back(bullet);
	}

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

