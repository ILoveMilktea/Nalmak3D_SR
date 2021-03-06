#include "stdafx.h"
#include "..\Include\GameManager.h"

GameManager* GameManager::m_instance = nullptr;

GameManager * GameManager::GetInstance()
{
	if (!m_instance)
	{
		auto instance = INSTANTIATE()->AddComponent<GameManager>();
		m_instance = instance->GetComponent<GameManager>();
		instance->SetDontDestroy(true);
	}

	return m_instance;
}

void GameManager::DeleteInstance()
{
	if (m_instance)
	{
		DESTROY(m_instance->GetGameObject());
	}
}


GameManager::GameManager(Desc * _desc)
{
}

GameManager::~GameManager()
{
}

void GameManager::Initialize()
{
}

void GameManager::Update()
{
}

bool GameManager::Get_StageClear(int _i) const
{
	return m_bStageClear[_i - 1];
}


void GameManager::Set_StageClear(int _i)
{
	if (m_bStageClear[_i - 1] == true)
	{
		assert(L"이미 깨져잇는 스테이지인데 뭔 소리고 ㅋㅋ;" && 0);
	}

	m_bStageClear[_i - 1] = true;
}
