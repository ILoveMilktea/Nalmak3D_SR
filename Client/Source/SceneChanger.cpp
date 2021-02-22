#include "stdafx.h"
#include "..\Include\SceneChanger.h"

#include "InputManager.h"


SceneChanger::SceneChanger(Desc * _desc)
{
	m_sceneName = _desc->sceneName;
	m_keyState = _desc->keyState;

}

SceneChanger::~SceneChanger()
{
}

void SceneChanger::Initialize()
{
	m_inputManager = InputManager::GetInstance();
	m_core = Core::GetInstance();
}

void SceneChanger::Update()
{
	NextSceneChange();
}

void SceneChanger::NextSceneChange()
{
	if (m_inputManager->GetKeyDown(m_keyState))
		m_core->LoadScene(m_sceneName);
}
