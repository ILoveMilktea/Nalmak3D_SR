#pragma once
#ifndef __UIFACTORY_H__
#define __UIFACTORY_H__

#include "Core.h"
class GameObject;

// Please Add CanvasRender First
class UIFactory
{

public:
	static GameObject* CreateFade(CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		CanvasRenderer::Desc desc;
		desc.group = _group;

		auto image = INSTANTIATE();
		image->AddComponent<CanvasRenderer>(&desc);
		image->AddComponent<SingleImage>();

		auto tex = ResourceManager::GetInstance()->GetResource<Texture>(L"UIBlack")->GetTexure(0);
		image->GetComponent<SingleImage>()->SetTexture(tex);

		return image;
	}

	static GameObject* CreateButton(CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		auto button = INSTANTIATE();
		button->AddComponent<CanvasRenderer>(&desc_cr);
		button->AddComponent<Button>();

		return button;
	}

	static GameObject* CreateButton(EventHandler _eventFunc, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Button::Desc desc;
		desc.eventFunc = _eventFunc;

		auto button = INSTANTIATE();
		button->AddComponent<CanvasRenderer>(&desc_cr);
		button->AddComponent<Button>(&desc);

		return button;
	}

	static GameObject* CreatePauseButton(CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

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
		toggle->AddComponent<CanvasRenderer>(&desc_cr);
		toggle->AddComponent<Toggle>(&desc);

		return toggle;
	}

	static GameObject* CreateToggle(CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Toggle::Desc desc;
		desc.onEventFunc = NULLEVENT;
		desc.offEventFunc = NULLEVENT;
		auto toggle = INSTANTIATE();
		toggle->AddComponent<CanvasRenderer>(&desc_cr);
		toggle->AddComponent<Toggle>(&desc);

		return toggle;
	}
	
	static GameObject* CreateRenderTargetWindow(const wstring& _name, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		SingleImage::Desc single;
		auto window = INSTANTIATE();
		window->AddComponent<SingleImage>();
		window->AddComponent<CanvasRenderer>(&desc_cr);

		window->GetComponent<SingleImage>()->
			SetTexture(ResourceManager::GetInstance()->GetResource<RenderTarget>(_name)->GetTexture());

		return window;
	}
};



#endif // !__UIFACTORY_H__
