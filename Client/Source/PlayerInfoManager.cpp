#include "stdafx.h"
#include "..\Include\PlayerInfoManager.h"
#include "ItemManager.h"
#include "PlayerShooter.h"
#include "PlayerItem.h"

PlayerInfoManager*::PlayerInfoManager::m_instance = nullptr;

PlayerInfoManager::PlayerInfoManager(Desc * _Desc)
{
	m_attack = _Desc->attack;
	m_maxHp = _Desc->maxHp;
	m_dirsensor = _Desc->dirsenser;
	m_hp = m_maxHp;

	m_maxSpeed = _Desc->maxSpeed;
	m_gold = _Desc->gold;

	m_player = nullptr;
}

PlayerInfoManager::~PlayerInfoManager()
{
	int a = 10;
}

void PlayerInfoManager::Initialize()
{
}

void PlayerInfoManager::Update()
{
	
	//DEBUG_LOG(L"Gold", m_gold);
	//DEBUG_LOG(L"현재 장착중인 주무기 ", m_currentlyWeapon[FIRST_PARTS]);
	//DEBUG_LOG(L"현재 장착중인 부 무장무기 ", m_currentlyWeapon[SECOND_PARTS]);


	m_timelimit -= TimeManager::GetInstance()->GetdeltaTime();
}

PlayerInfoManager * PlayerInfoManager::GetInstance()
{
	if (!m_instance)
	{
		auto instance = INSTANTIATE()->AddComponent<PlayerInfoManager>();
		m_instance = instance->GetComponent<PlayerInfoManager>();
		instance->SetDontDestroy(true);
	}
	return m_instance;
}

void PlayerInfoManager::DeleteInstance()
{
	if (m_instance)
	{
		DESTROY(m_instance->GetGameObject());
		m_instance = nullptr;
	}

}


void PlayerInfoManager::SetDamage(const int& _value)
{
	if (0 >= m_hp)
		return;

	m_hp += _value;
}

void PlayerInfoManager::SetHp(const int& _value)
{
	m_hp = _value;
}

void PlayerInfoManager::SetAttack(const int& _value)
{
	m_attack = _value;
}

void PlayerInfoManager::SetFullHp(const int& _value)
{
	m_maxHp = _value;
	m_hp = m_maxHp;
}

void PlayerInfoManager::SetSpeed(const float & _value)
{
	m_speed = _value;
}

void PlayerInfoManager::AddSpeed(float  _value)
{
	m_speed += _value * dTime;
	m_speed = Nalmak_Math::Clamp(m_speed, m_minSpeed, m_maxSpeed);
}

void PlayerInfoManager::SetDirSeneser(const float & _value)
{
	m_dirsensor = _value;
}

void PlayerInfoManager::SetRollAngle(const float & _value)
{
	m_rollAngle = _value;
}

void PlayerInfoManager::SetMinSpeed(const float & _value)
{
	m_minSpeed = _value;
}

void PlayerInfoManager::SetMaxSpeed(const float & _value)
{
	m_maxSpeed = _value;

}

void PlayerInfoManager::SetTimeLimit(const float & _value)
{
	m_timelimit = _value;
}

void PlayerInfoManager::SetScore(const float & _value)
{
	m_score = _value;
}

void PlayerInfoManager::SetPlayer(GameObject * _player)
{
	m_player = _player;
}

void PlayerInfoManager::MinGold(int _value)
{
	if (m_gold <= 0)
		return;
	m_gold -= _value;
}

const int & PlayerInfoManager::GetHp() const
{
	return m_hp;
}

const int & PlayerInfoManager::GetAttack() const
{
	return m_attack;
}

const int & PlayerInfoManager::GetMaxHp() const
{
	return m_maxHp;
}

const float & PlayerInfoManager::GetSpeed() const
{
	return m_speed;
}

const float & PlayerInfoManager::GetDirSenser() const
{
	return m_dirsensor;
}

bool PlayerInfoManager::EquipItem(PARTS_NUM eID, const wstring& _itemtype, const wstring & _equipItemName)
{
	// 1. 인벤에 있는 스트링이랑 상점에 있는 데이터  스트링이랑 맞으면

	//L"Weapon" == 임시
	wstring findItemType = L"";
	wstring findItemName = L"";

	for (auto& slotName : m_haveItemList)
	{
		if (_itemtype == slotName.first)
		{
			findItemType = slotName.first;
			for (auto & ItemName : slotName.second)
			{
				if (ItemName == _equipItemName)
				{
					findItemName = ItemName;
					break;
				}
			}
		}
	}

	PlayerItem* equipItem = ItemManager::GetInstance()->FindItemObject(findItemType, findItemName);
	if (!equipItem)
		return false;

	// 여기서 거르자
	if (findItemType == L"Weapon")
	{
		m_currentlyWeapon[eID] = equipItem->GetItmeInfo().itemName;
	}
	else if (findItemType == L"Skill")
	{
		m_currentlySkill[eID] = equipItem->GetItmeInfo().itemName;
	}

	return true;
}
