#include "stdafx.h"
#include "..\Include\StageManager.h"


#include "EvasionState.h"
#include "BossState.h"

#include "EnemyManager.h"
#include "NoneState.h"

StageManager* StageManager::m_instance = nullptr;

StageManager * StageManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		auto instance = INSTANTIATE()->AddComponent<StageManager>()->AddComponent<StateControl>();
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
	//m_strFirstScene = _desc->firstScene;


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



//float StageManager::Get_DogTime() const
//{
//	return 0.f;
//}
//
//float StageManager::Get_DogScore() const
//{
//	return 0.f;
//}

float StageManager::Get_EvasionTime() const
{
	return m_stateControl->GetState<EvasionState>(L"Evasion")->Get_Time();
}

float StageManager::Get_EvasionScore() const
{
	return m_stateControl->GetState<EvasionState>(L"Evasion")->Get_Score();
}

float StageManager::Get_BossTime() const
{
	return m_stateControl->GetState<BossState>(L"Boss")->Get_Time();
}

float StageManager::Get_BossSocre() const
{
	return m_stateControl->GetState<BossState>(L"Boss")->Get_Score();
}








//void StageManager::Set_DogScore(float _score)
//{
//	m_stateControl->GetState<DogFightState>(L"Dog_Fight")->Set_Score(_score);
//}
//
//void StageManager::Add_DogScore(float _score)
//{
//	m_stateControl->GetState<DogFightState>(L"Dog_Fight")->Add_Score(_score);
//}

void StageManager::Set_EvasionScore(float _score)
{
	m_stateControl->GetState<EvasionState>(L"Evasion")->Set_Score(_score);
}

void StageManager::Add_EvasionScore(float _score)
{
	m_stateControl->GetState<EvasionState>(L"Evasion")->Add_Score(_score);
}

void StageManager::Set_BossScore(float _score)
{
	m_stateControl->GetState<BossState>(L"Boss")->Set_Score(_score);
}

void StageManager::Add_BossScore(float _score)
{
	m_stateControl->GetState<BossState>(L"Boss")->Add_Score(_score);
}


void StageManager::ToTutorial()
{
	m_stateControl->SetState(L"Tutorial");
}

void StageManager::ToDog()
{
	m_stateControl->SetState(L"Dog_Fight");
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
