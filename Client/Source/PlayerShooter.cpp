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
	// 키값받아서 호출
	

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
	//if (m_useEquipment->GetShotCheck()) // 쐈으면
	//{
	//	m_shootTime -= dTime;
	//	if (m_shootTime <= 0)
	//	{
	//		m_shootTime = m_useEquipment->GetItmeInfo().delay;
	//		
	//		m_useEquipment->CreateBullet();
	//		m_useEquipment->SetShotCheck(false);
	//	}
	//}


	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_K))
	{
		SetEquipment(FIRST_PARTS);
	}
	else if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_L))
	{
		SetEquipment(THIRD_PARTS);
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

