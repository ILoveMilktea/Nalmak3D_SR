#include "stdafx.h"
#include "..\Include\ScriptEnd.h"

#include "InputManager.h"
#include "TimeManager.h"
#include "Scripter.h"

ScriptEnd::ScriptEnd()
{
}


ScriptEnd::~ScriptEnd()
{
}

void ScriptEnd::Initialize()
{
	m_scripter = m_stateControl->GetComponent<Scripter>();
}

void ScriptEnd::EnterState()
{
	m_scripter->ScriptOff();
}

void ScriptEnd::UpdateState()
{
	// 사실 script 끝난건데
	// 안도는 방법은 없나요
}

void ScriptEnd::ExitState()
{
}
