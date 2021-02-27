#include "stdafx.h"
#include "..\Include\PlayerInfoManager.h"


PlayerInfoManager*::PlayerInfoManager::m_instance = nullptr;

PlayerInfoManager::PlayerInfoManager(Desc * _Desc)
{
	m_attack = _Desc->attack;
	m_maxHp = _Desc->maxHp;
	m_dirsensor = _Desc->dirsenser;
	m_hp = m_maxHp;

	m_maxSpeed = _Desc->maxSpeed;
	 
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

void PlayerInfoManager::SetPlayer(GameObject * _player)
{
	m_player = _player;
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


void PlayerInfoManager::EquipWepon(PARTS_NUM _enumID, ItemDesc * _desc)
{
	m_playerItem[_enumID] = _desc;
}


