#include "stdafx.h"
#include "..\Include\AimMissile.h"




AimMissile::AimMissile(ItemDesc * _desc) : UseItem(&ItemDesc())
{
	m_itemtype = _desc->itemtype;
	m_useDelay = _desc->delay;
	m_shotSpeed = _desc->weaponSpeed;
	m_weaponAttak = _desc->weaponAttak;
	m_weaponAmmo = _desc->weaponAmmo; // �Ƹ�ī��Ʈ
}

void AimMissile::Initialize()
{
	UseItem::Initialize();
}

void AimMissile::Update()
{
	UseItem::Update();

}

void AimMissile::Shooting()
{
	//m_transform->position +=
	DEBUG_LOG(L"aimMissile", 0);
}
