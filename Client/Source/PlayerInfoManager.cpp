#include "stdafx.h"
#include "..\Include\PlayerInfoManager.h"
#include "ItemManager.h"
#include "PlayerShooter.h"
#include "PlayerItem.h"
#include "PlayerNone.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerTopViewMove.h"
#include "PlayerBossStageMove.h"
#include "PlayerEscapeState.h"
#include "PlayerSkillActor.h"
#include "..\..\Engine\Include\UIInteractor.h"
#include "UIWindowFactory.h"

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

GameObject * PlayerInfoManager::Player_Create()
{
	m_player = INSTANTIATE(OBJECT_TAG_PLAYER, L"player");

	if (m_player == nullptr)
	{
#ifdef _DEBUG
		assert(L"아ㅋㅋ; 플레이어 못 만든듯 ㅈㅅ ㅋㅋㅋ;;" && m_player);
#endif
		return nullptr;
	}

	m_player->SetScale(0.2f, 0.2f, 0.2f);

#pragma region Player Particle
	{
		ParticleRenderer::Desc render;
		render.particleDataName = L"player_zet_muzzle_left";
		m_player->AddComponent<ParticleRenderer>(&render);
		render.particleDataName = L"player_zet_muzzle_right";
		m_player->AddComponent<ParticleRenderer>(&render);
	}
#pragma endregion

	{
		PointLight::Desc lightDesc;
		lightDesc.color = Vector3(1, 0.3f, 0);
		lightDesc.radius = 2.f;
		lightDesc.diffuseIntensity = 5.f;
		auto light = INSTANTIATE()->AddComponent<PointLight>(&lightDesc)->SetPosition(0, 0, -1.5f);
		light->SetParents(m_player);

	}
	m_player->AddComponent<StateControl>();
	m_player->GetComponent<StateControl>()->AddState<PlayerNone>(L"playerNone");
	m_player->GetComponent<StateControl>()->AddState<PlayerIdle>(L"playerIdle");
	m_player->GetComponent<StateControl>()->AddState<PlayerMove>(L"playerMove");
	m_player->GetComponent<StateControl>()->AddState<PlayerTopViewMove>(L"playerTopViewMove");
	m_player->GetComponent<StateControl>()->AddState<PlayerBossStageMove>(L"playerBossMove");
	//status is related to skill.
	m_player->GetComponent<StateControl>()->AddState<PlayerEscapeState>(L"playerEscape");

	m_player->GetComponent<StateControl>()->InitState(L"playerIdle");

	MeshRenderer::Desc render;
	render.mtrlName = L"f15";
	render.meshName = L"f15";
	m_player->AddComponent<MeshRenderer>(&render);
	m_player->AddComponent<DrawGizmo>();
	m_player->AddComponent<PlayerShooter>();
	m_player->AddComponent<PlayerSkillActor>();

	SphereCollider::Desc player_col;
	player_col.radius = 1.f;
	m_player->AddComponent<SphereCollider>(&player_col);

	m_player->AddComponent<UIInteractor>();
	UIWindowFactory::StageWindow(m_player);


	return m_player;
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

GameObject * PlayerInfoManager::GetPlayer()
{
	if (m_player == nullptr)
	{
		Player_Create();
		return m_player;
	}

	return m_player;
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
