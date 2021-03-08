#include "stdafx.h"
#include "..\Include\ItemManager.h"
#include "PlayerItem.h"

#include "PlayerInfoManager.h"

#include "AimMissile.h"
#include "SmallCannon.h"
#include "Player_Weapon_Homing.h"
#include "Player_ClusterMissile.h"
#include "Player_EmpMissile.h"

#include "EscapeSkill.h"


ItemManager* ItemManager::m_instance = nullptr;

ItemManager::ItemManager(Desc * _Desc)
{
	m_playerMgr = PlayerInfoManager::GetInstance();

	CreateItem();
}

ItemManager::~ItemManager()
{
	for (auto& first : m_mapShopItem)
	{
		for (auto & value : first.second)
		{
			SAFE_DELETE(value);
		}
		first.second.clear();
	}
	m_mapShopItem.clear();
}

void ItemManager::Initialize()
{

}

void ItemManager::Update()
{
}

void ItemManager::CreateItem()
{
	ITEMINFO info;
	m_mapShopItem[L"Weapon"].reserve(5);
	m_mapShopItem[L"Skill"].reserve(5);

	{

		info.itemName = L"AimMissile";
		info.weaponType = WEAPON_MISSILE;
		info.weaponAttak = 50;
		info.costGold = 200;
		info.delay = 2.5f;
		info.weaponSpeed = 35.f;
		info.modelName = L"kfir_weapon1";
		m_mapShopItem[L"Weapon"].emplace_back(new AimMissile(info));
	}

	{
		info.itemName = L"Cannon";
		info.weaponType = WEAPON_CANNON;
		info.weaponAttak = 1;
		info.costGold = 100;
		info.delay = 0.15f;
		info.weaponSpeed = 45.f;
		info.modelName = L"su34_weapon1";
		m_mapShopItem[L"Weapon"].emplace_back(new SmallCannon(info));
	}

	{
		info.itemName = L"HomingMissile";
		info.weaponType = WEAPON_SINGLE_MISSILE;
		info.weaponAttak = 10;
		info.costGold = 100;
		info.delay = 0.25f;
		info.weaponSpeed = 45.f;
		info.modelName = L"su34_weapon2";
		m_mapShopItem[L"Weapon"].emplace_back(new Player_Weapon_Homing(info));
	}



	{
		info.itemName = L"ClusterMissile";
		info.weaponType = WEAPON_SINGLE_MISSILE;
		info.weaponAttak = 10;
		info.costGold = 50;
		info.delay = 1.f;
		info.weaponSpeed = 45.f;
		info.modelName = L"su34_weapon3";
		m_mapShopItem[L"Weapon"].emplace_back(new Player_ClusterMissile(info));
	}

	{
		info.itemName = L"Emp";
		info.weaponType = WEAPON_SINGLE_MISSILE;
		info.weaponAttak = 0;
		info.costGold = 0;
		info.delay = 1.f;
		info.weaponSpeed = 100.f;
		info.modelName = L"su34_weapon3";
		m_mapShopItem[L"Weapon"].emplace_back(new Player_EmpMissile(info));
	}

	/////////////////////
	{
		info.itemName = L"EscapeMove";
		info.costGold = 0;
		info.delay = 5.f;
		m_mapShopItem[L"Skill"].emplace_back(new EscapeSkill(info));
	}
	////////////////////
}

ItemManager * ItemManager::GetInstance()
{
	if (!m_instance)
	{
		auto Instance = INSTANTIATE()->AddComponent<ItemManager>();
		m_instance = Instance->GetComponent<ItemManager>();
		Instance->SetDontDestroy(true);
	}

	return m_instance;
}

void ItemManager::DeleteInstance()
{
	if (m_instance)
	{
		DESTROY(m_instance->GetGameObject());
	}
}

PlayerItem * ItemManager::FindItemObject(const wstring & _itemtype, const wstring & _typeValueName)
{
	PlayerItem * findItem = nullptr;

	for (auto & itemtype : m_mapShopItem)
	{
		if (_itemtype == itemtype.first)
		{
			for (auto & value : itemtype.second)
			{
				if (_typeValueName == value->GetItmeInfo().itemName)
				{
					findItem = value;
					break;
				}
			}
		}
	}

	return findItem;
}

bool ItemManager::BuyItem(const wstring & _itemName, const wstring & _typeValueName)
{
	PlayerItem* findItem = FindItemObject(_itemName, _typeValueName);

	for (auto & inven : m_playerMgr->GetInven())
	{
		if (_itemName == inven.first)
		{
			for(auto & ItemName : inven.second)
			{
				if(_typeValueName == ItemName)
					return false;// ?¸ë²¤??ê°™ì??´ë¦„?´ìžˆ?¼ë©´ ?¬ì??ŠëŠ”??
			}
		}

	}
	// ì°¾ëŠ” ?„ì´?œì´ ?†ëŠ” ê²½ìš°! ?¬ê¸° ?˜ì •??- ì¤€??
	if (!findItem)
		return false;

	int cost = findItem->GetItmeInfo().costGold;
	//
	if (m_playerMgr->GetGold() >= cost &&
		_typeValueName == findItem->GetItmeInfo().itemName)
	{
		m_playerMgr->MinGold(cost);
		m_playerMgr->GetInven()[_itemName].emplace_back(findItem->GetItmeInfo().itemName);

		return true;
	}
	else
	{
		return  false;
	}
}

wstring ItemManager::LoadItemModel(const wstring & _itemtype, const wstring & _itemName)
{
	PlayerItem* item = FindItemObject(_itemtype, _itemName);

	if (item)
		return item->GetModelName();
	else
		return L"";
}
