#include "stdafx.h"
#include "..\Include\DogFight_Stage1_1.h"


#include "PlayerInfoManager.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"


#include "MouseOption.h"
#include "SmoothFollow.h"

#include "EnemyManager.h"
#include "Enemy_Bullet_Manager.h"

#include "StageManager.h"
#include "UIWindowFactory.h"
#include "SceneChanger.h"
#include "PlayerNone.h"
#include "PlayerShooter.h"

#include "PlayerSkillActor.h"

#include "PlayerEscapeState.h"
#include "GameManager.h"
#include "Scripter.h"


DogFight_Stage1_1::DogFight_Stage1_1()
{
}


DogFight_Stage1_1::~DogFight_Stage1_1()
{
}

void DogFight_Stage1_1::Initialize()
{

}

void DogFight_Stage1_1::EnterState()
{
	m_pMainCam = Core::GetInstance()->GetMainCamera();
	assert(L"Can't Find MainCam at DogfightStage1Enter" && m_pMainCam);

	m_pPlayer = PlayerInfoManager::GetInstance()->GetPlayer();
	assert(L"Cant't Find Player at DogfightStage1Enter" && m_pPlayer);

	m_pScripter = Core::GetInstance()->FindObjectByName(OBJECT_TAG_SCRIPT, L"Tutorial_Script");
	assert(L"Can't Find Scripter at DogfightStage1Enter" && m_pScripter);

	m_pStageMgr = StageManager::GetInstance();
	assert(L"Can't Find m_pStageMgr  at DogfightStage1Enter" && m_pStageMgr);

	EnemyManager::GetInstance()->Spawn_S1P1_Normal();
	
	m_pScripter->GetComponent<StateControl>()->SetState(L"Pause");
}

void DogFight_Stage1_1::UpdateState()
{
	m_pStageMgr->GetComponent<StateControl>()->AddFloat(L"DogFight_Stage1_fTime", dTime);

	
	if (EnemyManager::GetInstance()->Get_EnemyCount() <= 0
		&& m_pScripter->GetComponent<Scripter>()->Get_DialogueIndex() == 5)
	{
		m_pScripter->GetComponent<StateControl>()->SetState(L"Ready");
		
	}

	if (m_pScripter->GetComponent<Scripter>()->Get_DialogueIndex() == 7)
	{
		m_stateControl->SetState(L"Tutorial_2");
	}

	
	

	





	

	//m_pStageMgr->ToScene(L"Tutorial_1");
	
	
	DEBUG_LOG(L"Current Scene", L"Stage1-Pattern1");
}

void DogFight_Stage1_1::ExitState()
{
}

//float DogFight_Stage1_1::Get_Time() const
//{
//	return m_fTutorialTime;
//}
//
//float DogFight_Stage1_1::Get_Score() const
//{
//	return m_fTutorialScore;
//}
//
//void DogFight_Stage1_1::Set_Score(float _score)
//{
//	m_fTutorialScore = _score;
//}
//
//void DogFight_Stage1_1::Add_Score(float _score)
//{
//	m_fTutorialScore += _score;
//}
//
//
//void DogFight_Stage1_1::Player_Faraway()
//{
//	Vector3 forward = m_Player->GetTransform()->GetForward();
//
//	m_Player->GetTransform()->position += forward * m_fSpd;
//}
//
//void DogFight_Stage1_1::Accelerate()
//{
//	m_fSpd = dTime * 500.f;
//}
