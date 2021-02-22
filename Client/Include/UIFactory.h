#pragma once
#ifndef __UIFACTORY_H__
#define __UIFACTORY_H__

#include "Core.h"
class GameObject;

class UIFactory
{

public:
	static GameObject* CreateButton()
	{
		auto button = INSTANTIATE();
		button->AddComponent<Button>();

		return button;
	}

	static GameObject* CreateButton(EventHandler _eventFunc)
	{
		Button::Desc desc;
		desc.eventFunc = _eventFunc;

		auto button = INSTANTIATE();
		button->AddComponent<Button>(&desc);

		return button;
	}

	static GameObject* CreatePauseButton()
	{
		Toggle::Desc desc;
		desc.onEventFunc = EventHandler([]() {
			TimeManager::GetInstance()->Pause();
		});
		desc.offEventFunc = EventHandler([]() {
			TimeManager::GetInstance()->Start();
		});
		desc.onImage = L"play";
		desc.offImage = L"pause";

		auto toggle = INSTANTIATE();
		toggle->AddComponent<Toggle>(&desc);

		return toggle;
	}

	static GameObject* CreateToggle()
	{
		auto toggle = INSTANTIATE();
		toggle->AddComponent<Toggle>();

		return toggle;
	}
	
};



#endif // !__UIFACTORY_H__
