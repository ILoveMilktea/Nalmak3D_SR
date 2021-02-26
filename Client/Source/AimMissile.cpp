#include "stdafx.h"
#include "..\Include\AimMissile.h"




AimMissile::AimMissile(Desc * _desc)  : UseItem(&UseItem::Desc())
{
	m_itemtype = _desc->useItem.itemtype;
	m_useDelay = _desc->useItem.delay;
	m_shotSpeed = _desc->useItem.weaponSpeed;
	m_weaponAttak = _desc->useItem.weaponAttak;
	m_weaponAmmo = _desc->useItem.weaponAmmo; // 아머카운트
}

void AimMissile::Initialize()
{
	UseItem::Initialize();
	SetWeapon();
}

void AimMissile::Update()
{
	UseItem::Update();
	DEBUG_LOG(L"aimMissile", m_itemtype);

	if (!ShotCheck)
	{
		missile[SIDE_TYPE::LEFT_SIDE]->GetTransform()->position = (Vector3{ -2.f, -1.f, 0.f });
		missile[SIDE_TYPE::RIGHT_SIDE]->GetTransform()->position = (Vector3{ 2.f, -1.f, 0.f });
	}
	else
	{
		
		missile[SIDE_TYPE::LEFT_SIDE]->GetTransform()->DeleteParent();
		missile[SIDE_TYPE::RIGHT_SIDE]->GetTransform()->DeleteParent();
		//Vector3 playerFrontDir = Vector3(0, 0, 1);
		missile[SIDE_TYPE::LEFT_SIDE]->GetTransform()->position += missile[SIDE_TYPE::LEFT_SIDE]->GetTransform()->GetForward() *m_shotSpeed * dTime;
		missile[SIDE_TYPE::RIGHT_SIDE]->GetTransform()->position += missile[SIDE_TYPE::LEFT_SIDE]->GetTransform()->GetForward() *m_shotSpeed * dTime;
	}
	
	/*missile[SIDE_TYPE::LEFT_SIDE]->GetTransform()->SetPosition(m_gameObject->GetTransform()->position + Vector3{ -3.f, -1.f, 0.f });
	missile[SIDE_TYPE::LEFT_SIDE]->GetTransform()->rotation = (m_gameObject->GetTransform()->rotation);

	missile[SIDE_TYPE::RIGHT_SIDE]->GetTransform()->SetPosition(m_gameObject->GetTransform()->position + Vector3{ 3.f, -1.f, 0.f });
	missile[SIDE_TYPE::RIGHT_SIDE]->GetTransform()->rotation = (m_gameObject->GetTransform()->rotation);*/

}

void AimMissile::Shooting()
{
	ShotCheck = true;
	
}

void AimMissile::SetWeapon()
{
		MeshRenderer::Desc render;
		render.mtrlName = L"niniz";
		render.meshName = L"box";

		missile[SIDE_TYPE::LEFT_SIDE] = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER)->AddComponent<MeshRenderer>(&render);
		missile[SIDE_TYPE::LEFT_SIDE]->SetParents(m_gameObject);
		missile[SIDE_TYPE::LEFT_SIDE]->GetTransform()->SetPosition( Vector3{ -2.f, -1.f, 0.f });

		missile[SIDE_TYPE::RIGHT_SIDE] = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER)->AddComponent<MeshRenderer>(&render);
		missile[SIDE_TYPE::RIGHT_SIDE]->SetParents(m_gameObject);
		missile[SIDE_TYPE::RIGHT_SIDE]->GetTransform()->SetPosition( Vector3{ 2.f, -1.f, 0.f });

}
