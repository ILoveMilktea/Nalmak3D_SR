#include "stdafx.h"
#include "..\Include\Player_Weapon_Homing.h"

#include "HomingBulletMove.h"
#include "EnemyDetector.h"

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

	switch (m_mode)
	{
	case Player_Weapon_Homing::SINGLE:
	{
		auto bullet = m_bullet.front();

		bullet->GetTransform()->position = bullet->GetTransform()->GetWorldPosition();
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
		VIBufferRenderer::Desc meshInfo;
		meshInfo.meshName = L"box";
		meshInfo.mtrlName = L"default";


		m_parents = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);

		auto bullet = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"Homing");
		bullet->AddComponent<VIBufferRenderer>(&meshInfo);
		bullet->SetParents(m_parents);
		bullet->SetPosition(0.f, -1.f, 0.f);
		bullet->SetScale(0.5f, 0.5f, 3.f);
		Vector3 eulerRotate = m_parents->GetTransform()->GetEulerRotation();
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
