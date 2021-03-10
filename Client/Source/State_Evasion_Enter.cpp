#include "stdafx.h"
#include "..\Include\State_Evasion_Enter.h"

#include "Stage2_Mainstream_Headers.h"
#include "Stage2_Mainstream_Define.h"

#include "PlayerInfoManager.h"
#include "EnemyManager.h"
#include "StageManager.h"
#include "FieldCameraInfo.h"
#include "CustomDebuger.h"

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
	m_stateControl->AddState<State_Evasion_Airfire>(_sn_airfire);
	m_stateControl->AddState<State_Evasion_Midboss>(_sn_midboss);
	m_stateControl->AddState<State_Evasion_MidbossDead>(_sn_midbossdead);

	m_mainCamera = Core::GetInstance()->GetMainCamera()->GetGameObject();
	m_mainCamera->GetComponent<StateControl>()->AddState<State_Camera_Wait>(_sn_camera_wait);
	m_mainCamera->GetComponent<StateControl>()->AddState<State_Camera_Evasion>(_sn_camera_evasion);
	m_mainCamera->GetComponent<StateControl>()->SetState(_sn_camera_wait);

	m_player = PlayerInfoManager::GetInstance()->GetPlayer();
	m_player->GetComponent<StateControl>()->AddState<State_Player_Wait>(_sn_player_wait);
	m_player->GetComponent<StateControl>()->AddState<State_Player_Evasion>(_sn_player_evasion);
	m_player->GetComponent<StateControl>()->SetState(_sn_player_wait);

	// phase 1 ui off
	CanvasGroup::GetInstance()->SetObjectActive(CANVAS_GROUP_STAGE1, false);

	// Cloud
	//ParticleRenderer::Desc desc;
	//desc.particleDataName = L"phase2_cloud";
	//auto cloudFloor = INSTANTIATE()->AddComponent<ParticleRenderer>(&desc);
	//cloudFloor->SetPosition(0.f, -50.f, 100.f);
}

void State_Evasion_Enter::UpdateState()
{
	// camera
	m_mainCamera->GetComponent<FieldCameraInfo>()->SetActive(false);
	m_mainCamera->SetPosition(Vector3(0.f, 40.f, -68.f));
	m_mainCamera->SetRotation(30.f, 0.f, 0.f);

	// player
	m_player->SetPosition(Vector3(0.f, 0.f, -10.f));
	m_player->SetScale(0.4f, 0.4f, 0.4f);
	m_player->SetRotation(0.f, 0.f, 0.f);
	
	m_player->AddComponent<CustomDebuger>();
	m_stateControl->SetState(_sn_airfire);
}

void State_Evasion_Enter::ExitState()
{
	m_mainCamera->AddComponent<FreeMove>();
	m_mainCamera->GetComponent<StateControl>()->SetState(_sn_camera_evasion);
	m_player->GetComponent<StateControl>()->SetState(_sn_player_evasion);
}
