#include "stdafx.h"
#include "..\Include\StageManager.h"
#include "DogFightState.h"
#include "ShootingState.h"
#include "BossState.h"


StageManager* StageManager::m_instance = nullptr;

StageManager * StageManager::GetInstance()
{
	if (!m_instance)
	{
		auto instance = INSTANTIATE()->AddComponent<StageManager>();
		m_instance = instance->GetComponent<StageManager>();
		instance->SetDontDestroy(true);
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
	m_gameObject->AddComponent<StateControl>();
	m_stateControl = GetComponent<StateControl>();
	m_stateControl->AddState<DogFightState>(L"dogFight");
	m_stateControl->AddState<ShootingState>(L"shooting");
	m_stateControl->AddState<BossState>(L"boss");
	m_stateControl->InitState(L"dogFight");
}

StageManager::~StageManager()
{
}

void StageManager::Initialize()
{
	
}

void StageManager::Update()
{



}
