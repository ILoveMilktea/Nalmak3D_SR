#pragma once
#ifndef __UIFACTORY_H__
#define __UIFACTORY_H__

#include "Core.h"
#include "EditController.h"
class GameObject;

// Please Add CanvasRender First
class UIFactory
{

public:
	static GameObject* CreateImage(CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		auto button = INSTANTIATE();
		button->AddComponent<CanvasRenderer>(&desc_cr);
		button->AddComponent<SingleImage>();

		return button;
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

	static GameObject* CreateText_Title_LEFT_White_Grid(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		Text::Desc desc;
		desc.width = 20;
		desc.height = 40;
		desc.text = _text;
		//desc.color = D3DCOLOR_RGBA(0, 0, 0, 255);
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;
		auto text = INSTANTIATE(OBJECT_TAG_UI, L"Title");
		text->AddComponent<CanvasRenderer>();
		text->AddComponent<Text>(&desc);

		SingleImage::Desc desc_si;
		desc_si.textureName = L"textgrid";
		text->AddComponent<SingleImage>(&desc_si);

		return text;
	}
	static GameObject* CreateText_Contents_LEFT_White_Grid(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		Text::Desc desc;
		desc.width = 14;
		desc.height = 24;
		desc.text = _text;
		//desc.color = D3DCOLOR_RGBA(0, 0, 0, 255);
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;
		auto text = INSTANTIATE(OBJECT_TAG_UI, L"Contents");
		text->AddComponent<CanvasRenderer>();
		text->AddComponent<Text>(&desc);

		SingleImage::Desc desc_si;
		desc_si.textureName = L"textgrid";
		text->AddComponent<SingleImage>(&desc_si);

		return text;
	}
	/*
	text + fill

	*/

public:
	static GameObject* CreateEditController()
	{
		auto controller = INSTANTIATE();
		controller->AddComponent<EditController>();

		return controller;
	}
};



#endif // !__UIFACTORY_H__
