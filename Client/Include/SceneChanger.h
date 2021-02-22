#pragma once
#include "Component.h"
class SceneChanger :
	public Component
{
public:
	struct Desc
	{
		wstring sceneName = L"";
		KEY_STATE keyState = {};
	};


public:
	SceneChanger(Desc* _desc);
	virtual ~SceneChanger();

public:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
public:
	void NextSceneChange();

private:
	InputManager* m_inputManager = nullptr;
	Core* m_core = nullptr;

private:
	wstring m_sceneName = L"";
	KEY_STATE m_keyState = {};
};

