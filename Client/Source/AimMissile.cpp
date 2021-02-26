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
	m_core = Core::GetInstance();
	SetWeapon(); // for init weapon
	MaxTime = m_useDelay;
}

void AimMissile::Update()
{
	UseItem::Update();
	if (0 > m_useDelay)
	{
		/*SetWeapon();*/
		ShotCheck = false;
		m_useDelay = MaxTime;
	}
	else if(ShotCheck)
		m_useDelay -= dTime;

	DEBUG_LOG(L"aimMissile", m_itemtype);
}

void AimMissile::Shooting(bool _check)
{
	ShotCheck = _check;

	m_core->FindObjectByName(OBJECT_TAG_BULLET_PLAYER, L"LEFT_TYPE")->GetComponent<Shooter>()->ShooterActive(true);
	m_core->FindObjectByName(OBJECT_TAG_BULLET_PLAYER, L"RIGHT_TYPE")->GetComponent<Shooter>()->ShooterActive(true);
}

void AimMissile::SetWeapon()
{
	MeshRenderer::Desc render;
	render.mtrlName = L"niniz";
	render.meshName = L"box";
	
	Shooter::Desc shooterInfo;
	shooterInfo.eMovePattern = MOVE_AXISDIR;
	shooterInfo.speed = m_shotSpeed;
	// 부모가 플레이어
	{
		shooterInfo.firePos = Vector3(-3.f, -0.5f, -1.f);
		auto leftType = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"LEFT_TYPE")->AddComponent<MeshRenderer>(&render)->AddComponent<Shooter>(&shooterInfo);
		//leftType->SetParents(m_gameObject);
	}

	{
		shooterInfo.firePos = Vector3(3.f, -0.5f, -1.f);
		auto rightType = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"RIGHT_TYPE")->AddComponent<MeshRenderer>(&render)->AddComponent<Shooter>(&shooterInfo);
		//rightType->SetParents(m_gameObject);
	}

	
}
