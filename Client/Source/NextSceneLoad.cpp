#include "stdafx.h"
#include "..\Include\NextSceneLoad.h"
#include "InputManager.h"
#include "Core.h"

NextSceneLoad::NextSceneLoad(Desc * _desc)
{
}

NextSceneLoad::~NextSceneLoad()
{
}

void NextSceneLoad::Initialize()
{
	m_transform->RotateRollPitchYaw(0, 45, 0);
}

void NextSceneLoad::Update()
{
	Vector3 test = m_transform->GetForward();
	m_transform->RotateRollPitchYaw(0, dTime, 0);
	//m_transform->position += m_transform->GetForward() * TimeManager::GetInstance()->GetdeltaTime();
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_ENTER))
	{
		Core::GetInstance()->LoadScene(L"stage");
	}
}

void NextSceneLoad::Release()
{
}
