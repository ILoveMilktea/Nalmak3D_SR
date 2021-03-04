#include "stdafx.h"
#include "Camera_ActionManager.h"



Camera_ActionManager*::Camera_ActionManager::m_instance = nullptr;

Camera_ActionManager::Camera_ActionManager(Desc * _desc)
{
}

Camera_ActionManager::~Camera_ActionManager()
{
}

void Camera_ActionManager::Initialize()
{
	
}

void Camera_ActionManager::Update()
{
}

Camera_ActionManager * Camera_ActionManager::GetInstance()
{
	if (!m_instance)
	{
		auto instance = INSTANTIATE()->AddComponent<Camera_ActionManager>();
		m_instance = instance->GetComponent<Camera_ActionManager>();

		{
			//m_instance->AddComponent<StateControl>();

		}

		instance->SetDontDestroy(true);
	}
	return m_instance;
}

void Camera_ActionManager::DeleteInstance()
{
	if (m_instance)
	{
		DESTROY(m_instance->GetGameObject());
		m_instance = nullptr;
	}
}
