#include "stdafx.h"
#include "..\Include\GarageSceneCameraMouseInput.h"
#include "GarageSceneCameraInfo.h"

GarageSceneCameraMouseInput::GarageSceneCameraMouseInput()
{
}


GarageSceneCameraMouseInput::~GarageSceneCameraMouseInput()
{
}

void GarageSceneCameraMouseInput::Initialize()
{
	m_player = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER)->GetTransform();
	m_garageCam = GetComponent<GarageSceneCameraInfo>();
}

void GarageSceneCameraMouseInput::EnterState()
{
	//m_garageCam->SetAxisTargetPos(Vector3(0, 5, 0));
	//m_garageCam->SetXAxisAngle(20);

	//m_garageCam->SetXMyAngle(0);
	//m_garageCam->SetXAxisAngle(-30);
	//m_garageCam->SetYAxisAngle(120);
	//m_garageCam->SetDistance(-15);
	//m_garageCam->SetFollowSpeed(3);
	//m_garageCam->SetRotateSpeed(3);
	//m_garageCam->SetLookSpeed(1);
	//m_garageCam->SetAxisTargetPos(Vector3(0, 1, 0));

	m_timer = 2;
}

void GarageSceneCameraMouseInput::UpdateState()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_A))
	{
		SetState(L"zoomIn");
		return;
	}

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_RIGHT_MOUSE))
	{
		Vector2 dir = InputManager::GetInstance()->GetMouseMoveDir();

		m_garageCam->AddXAxisAngle(dir.y * dTime * 100);
		m_garageCam->AddYAxisAngle(dir.x* dTime * 100);

		m_timer = 2.f;
	}
	else
	{
		m_timer -= dTime;

		if (m_timer < 0)
		{
			SetState(L"autoRotate");
			return;
		}

	}

	

}

void GarageSceneCameraMouseInput::ExitState()
{
}
