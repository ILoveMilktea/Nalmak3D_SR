#include "stdafx.h"
#include "PlayerKitSelector.h"
#include "Missile.h"
#include "UseItem.h"


PlayerKitSelector*::PlayerKitSelector::m_instance = nullptr;

PlayerKitSelector::PlayerKitSelector(Desc * _desc)
{

}

PlayerKitSelector::~PlayerKitSelector()
{
	for (auto& first : m_garageSlot)
	{
		for (auto & value : first.second)
		{
			SAFE_DELETE(value);
		}
		first.second.clear();
	}
	m_garageSlot.clear();
}

PlayerKitSelector * PlayerKitSelector::GetInstance()
{
	if (!m_instance)
	{
		auto instance = INSTANTIATE()->AddComponent<PlayerKitSelector>();
		m_instance = instance->GetComponent<PlayerKitSelector>();
		instance->SetDontDestroy(true);
	}
	return m_instance;
}




ItemDesc * PlayerKitSelector::FindSlotItme(const wstring & _name, ITEMTYPE _enumID)
{
	ItemDesc* itemInfo = nullptr;

	for (auto rPair : m_garageSlot)
	{
		if (_name == rPair.first)
		{
			for (auto& value : rPair.second)
			{
				if (_enumID == value->itemtype)
					itemInfo =  value;
			}
		}
	}

	assert("Nullptr, Can't Item Info Seraching..." && itemInfo);
	return itemInfo;
}

void PlayerKitSelector::DeleteInstance()
{

	if (m_instance)
		DESTROY(m_instance->GetGameObject());

}


void PlayerKitSelector::Initialize()
{
	m_garageSlot[L"Weapon"].reserve(2);

	{
		ItemDesc itemInfo;
		itemInfo.delay = 0.1f;
		itemInfo.itemtype = ITEMTYPE::ITEMTYPE_CANNON;
		itemInfo.weaponAttak = 5;
		itemInfo.weaponSpeed = 10.f;


		ItemDesc* ItemWepon = new ItemDesc(itemInfo);
		m_garageSlot[L"Weapon"].emplace_back(ItemWepon);
	}
	{

		ItemDesc itemInfo;
		itemInfo.delay = 3.f;
		itemInfo.itemtype = ITEMTYPE::ITEMTYPE_MISSILE;
		itemInfo.weaponAttak = 35;
		itemInfo.weaponSpeed = 15.f;

		ItemDesc* ItemWepon = new ItemDesc(itemInfo);
		m_garageSlot[L"Weapon"].emplace_back(ItemWepon);
	}


}

void PlayerKitSelector::Update()
{
	//DEBUG_LOG(L"POINTER", this);
	DEBUG_LOG(L"Size", m_garageSlot[L"Weapon"].size());

}
