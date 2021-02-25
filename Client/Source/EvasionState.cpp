#include "stdafx.h"
#include "..\Include\EvasionState.h"


EvasionState::EvasionState()
{
}


EvasionState::~EvasionState()
{
}

void EvasionState::Initialize()
{

}

void EvasionState::EnterState()
{
	m_MainCamera = Core::GetInstance()->FindFirstObject(OBJECT_TAG_CAMERA);

	if (m_MainCamera == nullptr)
	{
		assert(L"아 ㅋㅋ 메인 카메라 못찾겠다고 ㅋㅋ");
	}
	
	m_MainCamera->SetPosition(0.f, 100.f, 0.f);
	m_MainCamera->SetRotation(0.f, 0.f, 0.f);
	m_MainCamera->GetTransform()->RotateX(90.f);
	
	m_Player = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);
	if (m_Player == nullptr)
	{
		assert(L"플레이어 못받은거 같은데여 ㅋㅋ;;");
	}
	m_Player->GetTransform()->position = Vector3(0, 0, -50);
	m_Player->GetTransform()->SetRotation(0, 0, 0);

	m_bEnter = true;
}

void EvasionState::UpdateState()
{
	EnterProduce();
		
	


		
	DEBUG_LOG(L"Current Combat State : ", L"Evasion State");
	DEBUG_LOG(L"MainCam POS", m_MainCamera->GetTransform()->position);
	DEBUG_LOG(L"MainCam Rotx", m_MainCamera->GetTransform()->rotation.x);
	DEBUG_LOG(L"MainCam Roty", m_MainCamera->GetTransform()->rotation.y);
	DEBUG_LOG(L"MainCam Rotz", m_MainCamera->GetTransform()->rotation.z);
	DEBUG_LOG(L"Player Rotz", m_Player->GetTransform()->rotation.z);
}

void EvasionState::ExitState()
{
}

void EvasionState::EnterProduce()
{
	if (m_bEnter)
	{
		m_Player->GetTransform()->position.z += dTime * 50.f;

		if (m_Player->GetTransform()->position.z >= 0.f)
		{
			m_bEnter = false;
		}
	}
}
