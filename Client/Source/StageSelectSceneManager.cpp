#include "stdafx.h"
#include "StageSelectSceneManager.h"

StageSelectSceneManager* StageSelectSceneManager::m_instance = nullptr;

StageSelectSceneManager * StageSelectSceneManager::GetInstance()
{
	if (!m_instance)
	{
		auto instance = INSTANTIATE()->AddComponent<StageSelectSceneManager>();
		m_instance = instance->GetComponent<StageSelectSceneManager>();
		instance->SetDontDestroy(true);
	}

	return m_instance;
}

void StageSelectSceneManager::DeleteInstance()
{
	if (m_instance)
	{
		DESTROY(m_instance->GetGameObject());
		m_instance = nullptr;
	}
}

StageSelectSceneManager::StageSelectSceneManager(Desc * _desc)
{
}

StageSelectSceneManager::~StageSelectSceneManager()
{
	
}

void StageSelectSceneManager::Initialize()
{
}

void StageSelectSceneManager::Update()
{


}

const StageInfo & StageSelectSceneManager::GetStageInfo(int _index)
{
	return m_stageList[_index];
}

bool StageSelectSceneManager::SelectStage(int _index)
{
	if (_index >= 0 && _index < m_stageList.size())
	{
		m_currentSelectStageIndex = _index;

		return true;
	}

	return false;
}
