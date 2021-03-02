#include "stdafx.h"
#include "Scripter.h"

#include "ScriptReady.h"
#include "ScriptPlay.h"
#include "ScriptWait.h"
#include "ScriptEnd.h"
#include "ScriptPause.h"

Scripter::Scripter(Desc* _desc)
{
	m_title = _desc->title;
	m_script = _desc->script;
	m_dialogueList = _desc->startDialogue;
}

void Scripter::Initialize()
{
	m_dialogueIndex = 0;

	if (!m_dialogueList.empty())
	{
		Dialogue dialogue = m_dialogueList[0];

		m_title->SetText(dialogue.first);
		m_script->SetText(dialogue.second);
	}

	// state
	m_gameObject->AddComponent<StateControl>();
	m_state = GetComponent<StateControl>();

	m_state->AddState<ScriptReady>(L"Ready");
	m_state->AddState<ScriptPlay>(L"Play");
	m_state->AddState<ScriptWait>(L"Wait");
	m_state->AddState<ScriptEnd>(L"End");
	m_state->AddState<ScriptPause>(L"Pause");
	m_state->InitState(L"Ready");
}

void Scripter::Update()
{
}

void Scripter::Release()
{
	m_dialogueList.shrink_to_fit();
}

void Scripter::ScriptOn()
{
	m_title->GetGameObject()->SetActive(true);
	m_script->GetGameObject()->SetActive(true);
}

void Scripter::ScriptOff()
{
	m_title->GetGameObject()->SetActive(false);
	m_script->GetGameObject()->SetActive(false);
}

void Scripter::SetDialogue(vector<Dialogue> _dialogueList)
{
	m_dialogueList.clear();
	m_dialogueList = _dialogueList;
}

bool Scripter::LoadNextScript()
{
	++m_dialogueIndex;
	if (m_dialogueIndex == m_dialogueList.size())
		return false;

	Dialogue dialogue = m_dialogueList[m_dialogueIndex];

	m_title->SetText(dialogue.first);
	m_script->SetText(dialogue.second);

	return true;
}

void Scripter::LoadScriptByIndex(int _index)
{
	if (_index >= m_dialogueList.size() ||
		_index < 0)
	{
		return;
	}

	m_dialogueIndex = _index;

	Dialogue dialogue = m_dialogueList[m_dialogueIndex];

	m_title->SetText(dialogue.first);
	m_script->SetText(dialogue.second);
}
