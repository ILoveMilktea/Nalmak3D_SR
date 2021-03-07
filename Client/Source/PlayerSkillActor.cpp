#include "stdafx.h"
#include "..\Include\PlayerSkillActor.h"
#include "ItemManager.h"
#include "PlayerItem.h"

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
	
	//EquipSkill(FIRST_PARTS);
}

void PlayerSkillActor::Update()
{
	// 모든 
	if (m_inputMgr->GetKeyDown(KEY_STATE_1) && EquipSkill(FIRST_PARTS))
	{
		if (L"playerEscape" == m_stateControl->GetCurStateString())
			return;


		m_stateControl->SetState(L"playerEscape");

	}
	else if (m_inputMgr->GetKeyDown(KEY_STATE_2) && EquipSkill(SECOND_PARTS))
	{

	}

}

bool PlayerSkillActor::EquipSkill(PARTS_NUM _partsType)
{
	wstring slotInvenSkill = m_playerMgr->GetSkill(_partsType);
	if (L"" == slotInvenSkill) // 없다면?RETURN;
		return false;
	
	m_skillInfo = ItemManager::GetInstance()->FindItemObject(L"Skill", slotInvenSkill);
	return true;
}
