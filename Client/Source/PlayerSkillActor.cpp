#include "stdafx.h"
#include "..\Include\PlayerSkillActor.h"


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

	
	//EquipSkill(FIRST_PARTS);
}

void PlayerSkillActor::Update()
{
	// 모든 
	if (m_inputMgr->GetKeyDown(KEY_STATE_1) && EquipSkill(FIRST_PARTS))
	{
		/*int a = 10;*/
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
	
	return true;
}
