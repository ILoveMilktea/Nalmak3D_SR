#include "stdafx.h"
#include "..\Include\DogFight_Stage1_Enter.h"
#include "PlayerInfoManager.h"
#include "UIWindowFactory.h"
#include "Scripter.h"


DogFight_Stage1_Enter::DogFight_Stage1_Enter()
{
}


DogFight_Stage1_Enter::~DogFight_Stage1_Enter()
{
}

void DogFight_Stage1_Enter::Initialize()
{

}

void DogFight_Stage1_Enter::EnterState()
{
	m_pMainCam = Core::GetInstance()->GetMainCamera();
	assert(L"Can't Find MainCam at DogfightStage1Enter" && m_pMainCam);

	m_pPlayer = PlayerInfoManager::GetInstance()->GetPlayer();
	assert(L"Cant't Find Player at DogfightStage1Enter" && m_pPlayer);
	
	m_pScripter = Core::GetInstance()->FindObjectByName(OBJECT_TAG_SCRIPT, L"Tutorial_Script");
	assert(L"Can't Find Scripter at DogfightStage1Enter" && m_pScripter);
	
	m_pStageMgr = StageManager::GetInstance();
	assert(L"Can't Find m_pStageMgr  at DogfightStage1Enter" && m_pStageMgr);

}

void DogFight_Stage1_Enter::UpdateState()
{
	m_pStageMgr->GetComponent<StateControl>()->AddFloat(L"DogFight_Stage1_fTime", dTime);

	if (m_pScripter->GetComponent<Scripter>()->Get_DialogueIndex() == 5)
	{
		m_pStageMgr->ToScene(L"Tutorial_1");
	}

	DEBUG_LOG(L"Current Scene", L"Stage1-Enter");
}

void DogFight_Stage1_Enter::ExitState()
{
}
