#include "stdafx.h"
#include "..\Include\PlayerInfoManager.h"
#include "ItemManager.h"
#include "PlayerShooter.h"
#include "PlayerItem.h"
#include "PlayerNone.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerEscapeState.h"
#include "PlayerSkillActor.h"
#include "..\..\Engine\Include\UIInteractor.h"
#include "UIWindowFactory.h"
#include "Player_WindEffect.h"
#include "Player.h"
#include "Player_FarAway.h"
#include "Player_Evasion_Enter.h"
#include "Player_Evasion_Move.h"
#include "Player_Boss_Move.h"
#include "Player_Boss_Enter.h"
#include "Player_Evasion_Exit.h"

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

void PlayerInfoManager::SetKillCheck(const bool & _check)
{
	m_killCheck = _check;
}

void PlayerInfoManager::MinGold(int _value)
{
	if (m_gold <= 0)
		return;
	m_gold -= _value;
}

void PlayerInfoManager::SetWeaponSpawnPos(PARTS_NUM eID, bool _gargeCheck)
{
	wstring findWeaponName =  GetWeapon(eID);

	PlayerItem* findItem = ItemManager::GetInstance()->FindItemObject(L"Weapon", findWeaponName);

	//Mesh
	MeshRenderer::Desc meshInfo;
	//




	switch (findItem->GetItmeInfo().weaponType)
	{
	case WEAPON_CANNON:
		meshInfo.meshName = findItem->GetItmeInfo().modelName;
		findItem->SetCreatePos(Vector3(0.f, 0.f, 1.f));
		break;
	case WEAPON_MISSILE:
		if (m_pSideWeapon[0] || m_pSideWeapon[1])
		{
			DESTROY(m_pSideWeapon[0]);
			DESTROY(m_pSideWeapon[1]);

			m_pSideWeapon[0] = nullptr;
			m_pSideWeapon[1] = nullptr;
		}


		meshInfo.meshName = findItem->GetItmeInfo().modelName;
		meshInfo.mtrlName = L"su34";
		findItem->SetCreatePos(Vector3(0.5f, -0.1f, 0.f));
		findItem->SetMtrlName(meshInfo.mtrlName);
		
			m_pSideWeapon[0] = INSTANTIATE()->AddComponent<MeshRenderer>(&meshInfo);
			m_pSideWeapon[1] = INSTANTIATE()->AddComponent<MeshRenderer>(&meshInfo);
			m_pSideWeapon[0]->SetScale(0.2f, 0.2f, 0.2f);
			m_pSideWeapon[1]->SetScale(0.2f, 0.2f, 0.2f);

			if (_gargeCheck)
			{
				m_pSideWeapon[0]->SetParents(Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER));
				m_pSideWeapon[1]->SetParents(Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER));
			}
			else
			{
				m_pSideWeapon[0]->SetParents(GetPlayer());
				m_pSideWeapon[1]->SetParents(GetPlayer());
			}



			m_pSideWeapon[0]->SetPosition(findItem->GetItmeInfo().createPos);
			m_pSideWeapon[1]->SetPosition({ findItem->GetItmeInfo().createPos.x * -1.f,
				findItem->GetItmeInfo().createPos.y,
				findItem->GetItmeInfo().createPos.z });

		break;
	case WEAPON_SINGLE_MISSILE:
		if (m_pSingleWeapon)
		{
			DESTROY(m_pSingleWeapon);
			m_pSingleWeapon = nullptr;
		}

		meshInfo.meshName = findItem->GetItmeInfo().modelName;
		meshInfo.mtrlName = L"kfir";
		findItem->SetCreatePos(Vector3(0.f, -0.1f, -1.0f));
		findItem->SetMtrlName(meshInfo.mtrlName);


		m_pSingleWeapon = INSTANTIATE()->AddComponent<MeshRenderer>(&meshInfo);
		m_pSingleWeapon->SetScale(0.2f, 0.2f, 0.1f);
		

		if (_gargeCheck)
			m_pSingleWeapon->SetParents(Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER));
		else
			m_pSingleWeapon->SetParents(GetPlayer());
		
		m_pSingleWeapon->SetPosition(findItem->GetItmeInfo().createPos);
		break;
	}
}

GameObject * PlayerInfoManager::Player_Create()
{
	m_player = INSTANTIATE(OBJECT_TAG_PLAYER, L"player");


	if (m_player == nullptr)
	{
#ifdef _DEBUG
		assert(L"noooooooooo" && m_player);
#endif
		return nullptr;
	}
	
	m_player->SetScale(0.2f, 0.2f, 0.2f);

	Player::Desc player_desc;
	m_player->AddComponent<Player>(&player_desc);

#pragma region Player Particle
	// zet fire
	{
		ParticleRenderer::Desc render;
		render.particleDataName = L"player_zet_muzzle_left";
		m_player->AddComponent<ParticleRenderer>(&render);
		render.particleDataName = L"player_zet_muzzle_right";
		m_player->AddComponent<ParticleRenderer>(&render);
	}

	{
		Player_WindEffect::Desc wind;
		wind.leftTrailPos = Vector3(-1.7f, 0.14f, -0.05f);
		wind.rightTrailPos = Vector3(1.7f, 0.14f, -0.05f);
		wind.trailThick = 0.16f;
		m_player->AddComponent<Player_WindEffect>(&wind);
	}
	// zet distortion
	{
		ParticleRenderer::Desc	distortion;
		distortion.particleDataName = L"player_zet_distortion";
		auto effect = INSTANTIATE()->AddComponent<ParticleRenderer>(&distortion)->SetPosition(0.15f, 0.1f, -0.9f);
		effect->SetParents(m_player);
	}
	{
		ParticleRenderer::Desc	distortion;
		distortion.particleDataName = L"player_zet_distortion";
		auto effect = INSTANTIATE()->AddComponent<ParticleRenderer>(&distortion)->SetPosition(-0.15f, 0.1f, -0.9f);
		effect->SetParents(m_player);
	}


	{
		VIBufferRenderer::Desc vibuffer;
		vibuffer.meshName = L"screenQuad";
		vibuffer.mtrlName = L"particleDistortion";
		auto dist = INSTANTIATE()->AddComponent<VIBufferRenderer>(&vibuffer);
		dist->GetComponent<VIBufferRenderer>()->SetFrustumCulling(false);
	}
#pragma endregion
	// light
	{
		PointLight::Desc lightDesc;
		lightDesc.color = Vector3(1, 0.3f, 0);
		lightDesc.radius = 1.f;
		lightDesc.diffuseIntensity = 2.f;
		auto light = INSTANTIATE()->AddComponent<PointLight>(&lightDesc)->SetPosition(0, 0, -1.5f);
		light->SetParents(m_player);
	}
	// state
	m_player->AddComponent<StateControl>();
	m_player->GetComponent<StateControl>()->AddState<PlayerNone>(L"playerNone");
	m_player->GetComponent<StateControl>()->AddState<PlayerIdle>(L"playerIdle");
	m_player->GetComponent<StateControl>()->AddState<PlayerMove>(L"playerMove");
	
	m_player->GetComponent<StateControl>()->AddState<Player_FarAway>(L"playerFarAway");

	m_player->GetComponent<StateControl>()->AddState<Player_Evasion_Enter>(L"playerEvasion_Enter");
	m_player->GetComponent<StateControl>()->AddState<Player_Evasion_Move>(L"playerEvasion_Move");
	m_player->GetComponent<StateControl>()->AddState<Player_Evasion_Exit>(L"playerEvasion_Exit");
	
	m_player->GetComponent<StateControl>()->AddState<Player_Boss_Enter>(L"playerBoss_Enter");
	m_player->GetComponent<StateControl>()->AddState<Player_Boss_Move>(L"playerBoss_Move");

	//status is related to skill.
	m_player->GetComponent<StateControl>()->AddState<PlayerEscapeState>(L"playerEscape");
	m_player->GetComponent<StateControl>()->InitState(L"playerIdle");

	// mesh render
	MeshRenderer::Desc render;
	render.mtrlName = L"f15";
	render.meshName = L"f15";
	m_player->AddComponent<MeshRenderer>(&render);
	m_player->AddComponent<PlayerShooter>();
	m_player->AddComponent<PlayerSkillActor>();

	// collider
	SphereCollider::Desc player_col;
	player_col.radius = 1.f;
	m_player->AddComponent<SphereCollider>(&player_col);

	// ui
	m_player->AddComponent<UIInteractor>();
	UIWindowFactory::StageWindow(m_player);


	return m_player;
}

void PlayerInfoManager::Player_Release()
{
	m_player = nullptr;
}

void PlayerInfoManager::GrageWeaponRelease()
{
	if (m_pSideWeapon[0] || m_pSideWeapon[1])
	{
		DESTROY(m_pSideWeapon[0]);
		DESTROY(m_pSideWeapon[1]);

		m_pSideWeapon[0] = nullptr;
		m_pSideWeapon[1] = nullptr;
	}

	if (m_pSingleWeapon)
	{
		DESTROY(m_pSingleWeapon);
		m_pSingleWeapon = nullptr;
	}
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
