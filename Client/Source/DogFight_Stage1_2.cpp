#include "stdafx.h"
#include "..\Include\DogFight_Stage1_2.h"
#include "EnemyManager.h"
#include "PlayerInfoManager.h"
#include "StageManager.h"
#include "Scripter.h"


DogFight_Stage1_2::DogFight_Stage1_2()
{
}


DogFight_Stage1_2::~DogFight_Stage1_2()
{
}

void DogFight_Stage1_2::Initialize()
{
	
}

void DogFight_Stage1_2::EnterState()
{
	m_pMainCam = Core::GetInstance()->GetMainCamera();
	assert(L"Can't Find MainCam at DogfightStage1Enter" && m_pMainCam);

	m_pPlayer = PlayerInfoManager::GetInstance()->GetPlayer();
	assert(L"Cant't Find Player at DogfightStage1Enter" && m_pPlayer);

	m_pScripter = Core::GetInstance()->FindObjectByName(OBJECT_TAG_SCRIPT, L"Tutorial_Script");
	assert(L"Can't Find Scripter at DogfightStage1Enter" && m_pScripter);

	m_pStageMgr = StageManager::GetInstance();
	assert(L"Can't Find m_pStageMgr  at DogfightStage1Enter" && m_pStageMgr);

	EnemyManager::GetInstance()->Spawn_S1P1_Huge();

	m_pScripter->GetComponent<StateControl>()->SetState(L"Pause");
}

void DogFight_Stage1_2::UpdateState()
{

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_RIGHT_MOUSE) 
		&& m_pScripter->GetComponent<Scripter>()->Get_DialogueIndex() == 7)
	{
		m_pScripter->GetComponent<StateControl>()->SetState(L"Ready");
	}

	if (EnemyManager::GetInstance()->Get_EnemyCount() <= 0 
		&& m_pScripter->GetComponent<Scripter>()->Get_DialogueIndex() == 9)
	{
		m_pScripter->GetComponent<Scripter>()->LoadNextScript();
		m_stateControl->SetState(L"Tutorial_3");
	}


}

void DogFight_Stage1_2::ExitState()
{
}
