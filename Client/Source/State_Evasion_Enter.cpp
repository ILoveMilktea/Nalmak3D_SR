#include "stdafx.h"
#include "..\Include\State_Evasion_Enter.h"

#include "Mainstream_Headers.h"
#include "Mainstream_Define.h"

#include "EnemyManager.h"
#include "StageManager.h"

State_Evasion_Enter::State_Evasion_Enter()
{
}


State_Evasion_Enter::~State_Evasion_Enter()
{
}

void State_Evasion_Enter::Initialize()
{
}

void State_Evasion_Enter::EnterState()
{
	auto mainCamera = Core::GetInstance()->GetMainCamera();
	mainCamera->GetComponent<StateControl>()->AddState<State_Camera_Wait>(_sn_camera_wait);
	mainCamera->GetComponent<StateControl>()->SetState(_sn_camera_wait);

	auto player = PlayerInfoManager::GetInstance()->GetPlayer();
	player->GetComponent<StateControl>()->AddState<State_Player_Wait>(_sn_player_wait);
	player->GetComponent<StateControl>()->SetState(_sn_player_wait);

	// phase1 ui off
	CanvasGroup::GetInstance()->SetObjectActive(CANVAS_GROUP_STAGE1, false);
}

void State_Evasion_Enter::UpdateState()
{
}

void State_Evasion_Enter::ExitState()
{
}
