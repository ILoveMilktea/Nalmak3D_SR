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
	
	
	m_cannon = m_ItemManager->FindItemObject(L"Weapon", L"Cannon");
	m_shootTime = 0.5f;
	m_cannonCoolTime = 0.5f;
}

void PlayerShooter::Update()
{
	if (m_useEquipment)
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_MOUSE))
		{
			if (m_shootTime < 0)
			{
				m_useEquipment->ItemShot();
				m_shootTime = m_useEquipment->GetItmeInfo().delay;
			}
		}
		if (m_shootTime > 0)
		{
			m_shootTime -= dTime;
			if (m_shootTime <= 0)
				m_useEquipment->CreateBullet();
		}
	}
	if (m_cannon)
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_MOUSE))
		{
			if (m_cannonCoolTime < 0)
			{
				m_cannon->ItemShot();
				m_cannonCoolTime = m_cannon->GetItmeInfo().delay;
			}
		}
		if (m_cannonCoolTime > 0)
		{
			m_cannonCoolTime -= dTime;
			if (m_cannonCoolTime <= 0)
				m_cannon->CreateBullet();
		}
	}


	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_1))
	{
		SetEquipment(FIRST_PARTS);
	}
	else if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_2))
	{
		SetEquipment(SECOND_PARTS);
	}
	else if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_3))
	{
		SetEquipment(THIRD_PARTS);
	}
	else if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_4))
	{
		SetEquipment(FOURTH_PARTS);
	}
	else if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_5))
	{
		SetEquipment(FIFTH_PARTS);
	}
	else if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_6))
	{
		SetEquipment(SIXTH_PARTS);
	}
	
	//chet
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_C))
	{
		if (!m_cheatCheck)
		{
			ItemManager::GetInstance()->BuyItem(L"Weapon", L"AimMissile");
			ItemManager::GetInstance()->BuyItem(L"Weapon", L"HomingMissile");
			ItemManager::GetInstance()->BuyItem(L"Weapon", L"ClusterMissile");
			ItemManager::GetInstance()->BuyItem(L"Weapon", L"Emp");

			PlayerInfoManager::GetInstance()->EquipItem(FIRST_PARTS, L"Weapon", L"AimMissile");
			PlayerInfoManager::GetInstance()->EquipItem(SECOND_PARTS, L"Weapon", L"HomingMissile");
			PlayerInfoManager::GetInstance()->EquipItem(THIRD_PARTS, L"Weapon", L"ClusterMissile");
			PlayerInfoManager::GetInstance()->EquipItem(FOURTH_PARTS, L"Weapon", L"Emp");

			PlayerInfoManager::GetInstance()->SetWeaponSpawnPos(FIRST_PARTS ,false);
			PlayerInfoManager::GetInstance()->SetWeaponSpawnPos(SECOND_PARTS, false);
			PlayerInfoManager::GetInstance()->SetWeaponSpawnPos(THIRD_PARTS, false);
			PlayerInfoManager::GetInstance()->SetWeaponSpawnPos(FOURTH_PARTS, false);
			PlayerInfoManager::GetInstance()->GrageWeaponRelease();
			//SetEquipment(FIRST_PARTS);

			SetEquipment(FIRST_PARTS);
			m_cheatCheck = true;
		}
	

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

