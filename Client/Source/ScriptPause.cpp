#include "stdafx.h"
#include "..\Include\ScriptPause.h"

#include "InputManager.h"
#include "TimeManager.h"
#include "Scripter.h"


ScriptPause::ScriptPause()
{
}


ScriptPause::~ScriptPause()
{
}

void ScriptPause::Initialize()
{
	m_scripter = m_stateControl->GetComponent<Scripter>();
	m_timeManager = TimeManager::GetInstance();
}

void ScriptPause::EnterState()
{
}

void ScriptPause::UpdateState()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_K))
	{
		SetState(GetString(L"PrevState"));
		SetString(L"PrevState", L"Pause");
		return;
	}
}

void ScriptPause::ExitState()
{
}
