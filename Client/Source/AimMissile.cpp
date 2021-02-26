#include "stdafx.h"
#include "..\Include\AimMissile.h"
#include "Shooter.h"


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
}

void AimMissile::Shooting()
{
	
}

void AimMissile::SetWeapon()
{
	MeshRenderer::Desc render;
	render.mtrlName = L"niniz";
	render.meshName = L"box";

	INSTANTIATE(OBJECT_TAG_BULLET_PLAYER , L"LEFT_TYPE")->AddComponent<MeshRenderer>(&render)->AddComponent<Shooter>();
	INSTANTIATE(OBJECT_TAG_BULLET_PLAYER,  L"RIGHT_TYPE")->AddComponent<MeshRenderer>(&render)->AddComponent<Shooter>();
}
