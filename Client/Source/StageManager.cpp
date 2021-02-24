#include "stdafx.h"
#include "..\Include\StageManager.h"
#include "DogFightState.h"
#include "EvasionState.h"
#include "BossState.h"


StageManager* StageManager::m_instance = nullptr;

StageManager * StageManager::GetInstance()
{
	if (!m_instance)
	{
		auto instance = INSTANTIATE()->AddComponent<StageManager>();
		m_instance = instance->GetComponent<StageManager>();
		//instance->SetDontDestroy(true);
	}

	return m_instance;
}

void StageManager::DeleteInstance()
{
	if (m_instance)
	{
		DESTROY(m_instance->GetGameObject());
	}
}

StageManager::StageManager(Desc * _desc)
{

}

StageManager::~StageManager()
{
}

void StageManager::Initialize()
{
	m_gameObject->AddComponent<StateControl>();
	m_stateControl = GetComponent<StateControl>();
	m_stateControl->AddState<DogFightState>(L"Dog_Fight");
	m_stateControl->AddState<EvasionState>(L"Evasion");
	m_stateControl->AddState<BossState>(L"Boss");
	m_stateControl->InitState(L"Dog_Fight");
}

void StageManager::Update()
{

	if (m_stateControl->CompareState(L"Dog_Fight"))
	{
		if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F2))
		{

		}
	}


}

void StageManager::ToEvasion()
{
	m_stateControl->SetState(L"Evasion");
}

void StageManager::ToBoss()
{
	m_stateControl->SetState(L"Boss");
}

void StageManager::ToScene(const wstring & _sceneName)
{
	m_stateControl->SetState(_sceneName);
}
