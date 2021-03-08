#include "stdafx.h"
#include "PlayerShooter.h"
#include "PlayerItem.h"
#include "PlayerInfoManager.h"
#include "ItemManager.h"

PlayerShooter::PlayerShooter(Desc * _Desc)
{
}

PlayerShooter::~PlayerShooter()
{
}

void PlayerShooter::Initialize()
{
	m_playerMgr = PlayerInfoManager::GetInstance();
	m_ItemManager = ItemManager::GetInstance();

	//SetEquipment(FIRST_PARTS);
	SetEquipment(PARTS_NUM::FIRST_PARTS);
	SetEquipment(PARTS_NUM::SECOND_PARTS);
	SetEquipment(PARTS_NUM::THIRD_PARTS);

	m_shootTime = 0.5f;
}

void PlayerShooter::Update()
{
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_MOUSE))
	{
		if (m_useEquipment && m_shootTime < 0)
		{
			m_useEquipment->ItemShot();
			m_shootTime = m_useEquipment->GetItmeInfo().delay;
		}
	}
	if (m_useEquipment && m_shootTime > 0)
	{
		m_shootTime -= dTime;
		if (m_shootTime <= 0)
			m_useEquipment->CreateBullet();
	}


	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_1))
	{
		SetEquipment(FIRST_PARTS);
	}
	else if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_2))
	{
		SetEquipment(SECOND_PARTS);
	}

	if (m_useEquipment)
	{
		DEBUG_LOG(L"현재 장착한 무기", m_useEquipment->GetItmeInfo().itemName);
	}
}

void PlayerShooter::SetEquipment(PARTS_NUM _weaponName)
{
	if (m_prevParts == _weaponName)
		return;

	m_prevParts = _weaponName;
	

	wstring equipWeaponName = m_playerMgr->GetWeapon(_weaponName);
	if (L"" == equipWeaponName)
		return;
	if(m_useEquipment)
		m_useEquipment->DeleteBullet();
	m_useEquipment = m_ItemManager->FindItemObject(L"Weapon", equipWeaponName);
	

	m_useEquipment->CreateBullet();
	m_shootTime = m_useEquipment->GetItmeInfo().delay;

}

void PlayerShooter::Shoot()
{
	m_useEquipment->CreateBullet();
	m_useEquipment->ItemShot();
}

void PlayerShooter::EquipByItemName(const wstring & _itemName)
{
	if (m_useEquipment)
		m_useEquipment->DeleteBullet();

	m_useEquipment = m_ItemManager->FindItemObject(L"Weapon", _itemName);
}

