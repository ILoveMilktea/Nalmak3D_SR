#include "stdafx.h"
#include "..\Include\ScriptReady.h"

#include "TimeManager.h"
#include "Scripter.h"

ScriptReady::ScriptReady()
{
}


ScriptReady::~ScriptReady()
{
}

void ScriptReady::Initialize()
{
	SetFloat(L"Timer", 0.f);
	SetString(L"PrevState", L"Ready");
	m_scripter = m_stateControl->GetComponent<Scripter>();
	m_timeManager = TimeManager::GetInstance();

	m_scripter->ScriptOff();
}

void ScriptReady::EnterState()
{
	//if (GetString(L"PrevState") == L"Pause")
	//	m_timer = GetFloat(L"Timer");
	//else
	m_timer = 0;
	
	if (!m_scripter->LoadNextScript())
	{
		SetState(L"End");
		return;
	}
}

void ScriptReady::UpdateState()
{
	m_timer += m_timeManager->GetdeltaTime();
	
	//if (m_timeManager->IsPause())
	//{
	//	SetFloat(L"Timer", m_timer);
	//	SetString(L"PrevState", L"Ready");
	//	SetState(L"Pause");
	//	return;
	//}

	if (m_timer > 1.f)
	{
		SetState(L"Play");
		return;
	}
}

void ScriptReady::ExitState()
{
	m_scripter->ScriptOn();
}
