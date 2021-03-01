#include "stdafx.h"
#include "..\Include\ItemManager.h"
#include "PlayerItem.h"

#include "PlayerInfoManager.h"

//플레이어 아이템
#include "AimMissile.h"
#include "SmallCannon.h"
// 플레이어 스킬

#include "EscapeSkill.h"

ItemManager* ItemManager::m_instance = nullptr;

ItemManager::ItemManager(Desc * _Desc)
{
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
	// 겟인스턴스 이후 컴퍼넌트가 추가된 이후 이니셜라이즈
	// unordered_map<wstring, vector<class PlayerItem*>> m_mapShopItem;
	ITEMINFO info;
	m_mapShopItem[L"Weapon"].reserve(5);
	m_mapShopItem[L"Skill"].reserve(5);

	m_playerMgr = PlayerInfoManager::GetInstance();

	{
		
		info.itemName = L"AimMissile";
		info.costGold = 200;
		info.delay = 2.5f;
		info.weaponSpeed = 35.f;
		m_mapShopItem[L"Weapon"].emplace_back(new AimMissile(info));
	}

	{
		ITEMINFO info;
		info.itemName = L"Cannon";
		info.costGold = 100;
		info.delay = 0.25f;
		info.weaponSpeed = 45.f;

		m_mapShopItem[L"Weapon"].emplace_back(new SmallCannon(info));
	}

	{
		ITEMINFO info;
		info.itemName = L"EscapeMove";
		info.costGold = 0.f;
		info.delay = 5.f;
		m_mapShopItem[L"Skill"].emplace_back(new EscapeSkill(info));

	}

	//스킬 사서쓸지 그냥 갖고있을지 몰라서 일단 사놓음.
	{
		BuyItem(L"Skill", L"EscapeMove");
	}



}

void ItemManager::Update()
{
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
	
	for (auto & inven : m_playerMgr->GetInven()) // 인벤에 같은이름이있으면 사지않는다.
	{
		if (_itemName == inven.first)
		{
			for(auto & ItemName : inven.second)
			{
				if(_typeValueName == ItemName)
					return false;
			}
		}
		
	}
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

