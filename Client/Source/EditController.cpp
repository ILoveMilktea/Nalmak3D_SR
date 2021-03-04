#include "stdafx.h"
#include "..\Include\EditController.h"
#include "EnemyManager.h"
#include "UIManager.h"

EditController::EditController(Desc * _desc)
{
}

void EditController::Initialize()
{
	m_input = InputManager::GetInstance();
	m_editMode = false;
}

void EditController::Update()
{
	if (m_input->GetKeyDown(KEY_STATE_ESC))
	{
		PostQuitMessage(0);
	}

	if (m_input->GetKeyDown(KEY_STATE_TAB))
		m_editMode = true;
	
	if (!m_editMode)
		return;

	if (m_input->GetKeyDown(KEY_STATE_F1))
	{
	}
	if (m_input->GetKeyDown(KEY_STATE_F2))
	{

	}
	if (m_input->GetKeyDown(KEY_STATE_F3))
	{
	}
	if (m_input->GetKeyDown(KEY_STATE_F4))
	{
		EnemyManager::GetInstance()->Destroy_AllEnemy();
	}
	if (m_input->GetKeyDown(KEY_STATE_F5))
	{
		auto alarm = UIFactory::Prefab_Stage_Alarm(UI_Alarm::WARNING, L"warning message", CANVAS_GROUP_STAGEWND);
		alarm->GetComponent<UI_Alarm>()->AlarmOnAnim();
		UIManager::GetInstance()->AddAlarm(alarm->GetComponent<UI_Alarm>());
		//UIManager::GetInstance()->SkillRotateOn(0);
	}
	if (m_input->GetKeyDown(KEY_STATE_F6))
	{
		auto alarm = UIFactory::Prefab_Stage_Alarm(UI_Alarm::NOTICE, L"notice message", CANVAS_GROUP_STAGEWND);
		alarm->GetComponent<UI_Alarm>()->AlarmOnAnim();
		UIManager::GetInstance()->AddAlarm(alarm->GetComponent<UI_Alarm>());
		//UIManager::GetInstance()->SkillRotateOn(1);
	}
	if (m_input->GetKeyDown(KEY_STATE_F7))
	{
		auto alarm = UIFactory::Prefab_Stage_Alarm(UI_Alarm::KILL, L"kill message", CANVAS_GROUP_STAGEWND);
		alarm->GetComponent<UI_Alarm>()->AlarmOnAnim();
		UIManager::GetInstance()->AddAlarm(alarm->GetComponent<UI_Alarm>());
		//UIManager::GetInstance()->SkillRotateOn(2);

	}
	if (m_input->GetKeyDown(KEY_STATE_F8))
	{
		//UIManager::GetInstance()->SkillRotateOn(3);
	}
	if (m_input->GetKeyDown(KEY_STATE_F9))
	{
		UIManager::GetInstance()->SkillRotateOn(4);
	}
}
