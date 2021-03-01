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
}

void PlayerInfoManager::Initialize()
{
}

void PlayerInfoManager::Update()
{
	DEBUG_LOG(L"Gold", m_gold);
	DEBUG_LOG(L"인벤사이즈", m_haveItemList.size());

	DEBUG_LOG(L"현재 장착중인 주무기 ", m_Culweapon[FIRST_PARTS]);
	DEBUG_LOG(L"현재 장착중인 부 무장무기 ", m_Culweapon[SECOND_PARTS]);


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
		DESTROY(m_instance->GetGameObject());

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

bool PlayerInfoManager::EquipItem(PARTS_NUM eID, const wstring & _equipItemName)
{
	// 1. 인벤에 있는 스트링이랑 상점에 있는 데이터  스트링이랑 맞으면

	//L"Weapon" == 임시
	wstring findString = L"";

	for (auto& value : m_haveItemList)
	{
		if (value == _equipItemName)
		{
			findString = value;
			break;
		}
	}

	PlayerItem* equipItem = ItemManager::GetInstance()->FindItemObject(L"Weapon", findString);
	if (!equipItem)
		return false;

	switch (eID)
	{
	case FIRST_PARTS:
		m_Culweapon[FIRST_PARTS] = equipItem->GetItmeInfo().itemName;
	
		break;
	case SECOND_PARTS:
		m_Culweapon[SECOND_PARTS] = equipItem->GetItmeInfo().itemName;
		
		break;
	case THIRD_PARTS:
		break;
	case PARTS_MAX:
		break;
	default:
		break;
	}

	return true;
}
