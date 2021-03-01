#include "stdafx.h"
#include "..\Include\ScriptPlay.h"

#include "TimeManager.h"
#include "Scripter.h"

ScriptPlay::ScriptPlay()
{
}


ScriptPlay::~ScriptPlay()
{
}

void ScriptPlay::Initialize()
{
	m_scripter = m_stateControl->GetComponent<Scripter>();
	m_timeManager = TimeManager::GetInstance();
}

void ScriptPlay::EnterState()
{
	m_timer = 0;
}

void ScriptPlay::UpdateState()
{
	// 원래 여기서 typing 처리입니다

	m_timer += m_timeManager->GetdeltaTime();

	if (m_timeManager->IsPause())
	{
		SetFloat(L"Timer", m_timer);
		SetString(L"PrevState", L"Play");
		SetState(L"Pause");
		return;
	}

	if (m_timer > 1.f)
	{
		SetState(L"Wait");
		return;
	}
}

void ScriptPlay::ExitState()
{

}
