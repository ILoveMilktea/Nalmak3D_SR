#include "stdafx.h"
#include "..\Include\PlayerSkillActor.h"
#include "ItemManager.h"
#include "PlayerItem.h"
#include "ScaleDampingDeffender.h"
#include "PlayerInfoManager.h"
PlayerSkillActor::PlayerSkillActor(Desc * _Desc)
{
}

PlayerSkillActor::~PlayerSkillActor()
{
}

void PlayerSkillActor::Initialize()
{
	m_playerMgr = PlayerInfoManager::GetInstance();
	m_inputMgr = InputManager::GetInstance();
	m_stateControl = m_gameObject->GetComponent<StateControl>();
	m_core = Core::GetInstance();

	//EquipSkill(FIRST_PARTS);
}

void PlayerSkillActor::Update()
{
	FirstStart();


	if (m_inputMgr->GetKeyDown(KEY_STATE_X)/* && EquipSkill(FIRST_PARTS)*/)
	{
		int a = 10;
		if (!m_core->GetObjectList(OBJECT_TAG_PLAYER_SHIELD).empty())
			return;


			VIBufferRenderer::Desc meshInfo;
			//meshInfo.mtrlName = L"debugCollider";
			meshInfo.mtrlName = L"default_red";
			meshInfo.meshName = L"sphere";


			SphereCollider::Desc sphereColliderInfo;
			sphereColliderInfo.collisionLayer = COLLISION_LAYER_SHIELD;
			sphereColliderInfo.radius = 1.f;

			auto shield = INSTANTIATE(OBJECT_TAG_PLAYER_SHIELD, L"playerNormalShield")->
				AddComponent<VIBufferRenderer>(&meshInfo)->
				AddComponent<ScaleDampingDeffender>()->
				AddComponent<SphereCollider>(&sphereColliderInfo);
			shield->SetParents(m_gameObject);



	}
	else if (m_inputMgr->GetKeyDown(KEY_STATE_C) && EquipSkill(SECOND_PARTS))
	{

	}

}

void PlayerSkillActor::FirstStart()
{
	if (!m_cheat)
	{
		ItemManager::GetInstance()->BuyItem(L"Skill", L"EscapeMove");
		PlayerInfoManager::GetInstance()->EquipItem(FIFTH_PARTS, L"Skill", L"EscapeMove");
		EquipSkill(FIFTH_PARTS);
		m_cheat = true;
	}
}

bool PlayerSkillActor::EquipSkill(PARTS_NUM _partsType)
{
	wstring slotInvenSkill = m_playerMgr->GetSkill(_partsType);
	if (L"" == slotInvenSkill) // ���ٸ�?RETURN;
		return false;

	m_skillInfo = ItemManager::GetInstance()->FindItemObject(L"Skill", slotInvenSkill);
	return true;
}
