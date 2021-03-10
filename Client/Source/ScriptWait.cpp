#include "stdafx.h"
#include "..\Include\ScriptWait.h"

#include "InputManager.h"
#include "TimeManager.h"
#include "Scripter.h"

ScriptWait::ScriptWait()
{
}


ScriptWait::~ScriptWait()
{
}

void ScriptWait::Initialize()
{
	m_scripter = m_stateControl->GetComponent<Scripter>();
	m_timeManager = TimeManager::GetInstance();
}

void ScriptWait::EnterState()
{

}

void ScriptWait::UpdateState()
{
	//if (m_timeManager->IsPause())
	//{
	//	SetString(L"PrevState", L"Wait");
	//	SetState(L"Pause");
	//	return;
	//}
	//else 
	//{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_ENTER)
		|| InputManager::GetInstance()->GetKeyDown(KEY_STATE_SPACE))
	{
		SetState(L"Ready");
		return;
	}
	//}
		
}

void ScriptWait::ExitState()
{
	m_scripter->ScriptOff();
}
