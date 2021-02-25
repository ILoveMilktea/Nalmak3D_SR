#pragma once
#ifndef __UIFACTORY_H__
#define __UIFACTORY_H__

#include "Core.h"
#include "EditController.h"
class GameObject;

//===============================
// Please Add CanvasRender First
//===============================
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

	static GameObject* CreateImage(CANVAS_GROUP _group = CANVAS_GROUP_NONE, const wstring& _name = L"defaultUI")
	{
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;
		SingleImage::Desc desc_si;
		desc_si.textureName = _name;

		auto button = INSTANTIATE();
		button->AddComponent<CanvasRenderer>(&desc_cr);
		button->AddComponent<SingleImage>(&desc_si);

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

	static GameObject* Prefab_MenuTitle(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		Text::Desc desc;
		desc.width = 12;
		desc.height = 30;
		desc.text = _text;
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;
		
		auto text = INSTANTIATE(OBJECT_TAG_UI, L"MenuTitle");
		text->AddComponent<CanvasRenderer>();
		text->AddComponent<Text>(&desc);

		text->SetScale(760.f, 40.f);
		return text;
	}
	static GameObject* Prefab_MenuButton(EventHandler _eventFunc, const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// button
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Button::Desc desc_bt;
		desc_bt.eventFunc = _eventFunc;

		auto menu = INSTANTIATE(OBJECT_TAG_UI, L"MenuButton");
		menu->AddComponent<CanvasRenderer>(&desc_cr);
		menu->AddComponent<Button>(&desc_bt);

		menu->GetComponent<Button>()->ChangeNormalColor(1.f, 1.f, 1.f, 0.f);
		menu->GetComponent<Button>()->ChangeHighlightColor(0.f, 0.5f, 0.8f, 0.5f);
		menu->GetComponent<Button>()->ChangePressedColor(0.9f, 0.6f, 0.f, 0.5f);
		menu->GetComponent<Button>()->ChangeDisableColor(0.2f, 0.2f, 0.2f, 0.5f);

		// text
		Text::Desc desc;
		desc.width = 10;
		desc.height = 25;
		desc.text = _text;
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		menu->AddComponent<Text>(&desc);

		menu->SetScale(760.f, 30.f);
		return menu;
	}
	
	static GameObject* Prefab_ItemTitle(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		Text::Desc desc;
		desc.width = 10;
		desc.height = 25;
		desc.text = _text;
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		auto subtitle = INSTANTIATE(OBJECT_TAG_UI, L"ItemTitle");
		subtitle->AddComponent<CanvasRenderer>();
		subtitle->AddComponent<Text>(&desc);
		subtitle->SetScale(380.f, 30.f);
		return subtitle;
	}
	static GameObject* Prefab_ItemSubtitle(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		Text::Desc desc;
		desc.width = 8;
		desc.height = 20;
		desc.text = _text;
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		auto subtitle = INSTANTIATE(OBJECT_TAG_UI, L"ItemSubtitle");
		subtitle->AddComponent<CanvasRenderer>();
		subtitle->AddComponent<Text>(&desc);
		subtitle->SetScale(380.f, 25.f);
		return subtitle;
	}
	static GameObject* Prefab_ItemContents_Name(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		Text::Desc desc;
		desc.width = 10;
		desc.height = 25;
		desc.text = _text;
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		auto contents = INSTANTIATE(OBJECT_TAG_UI, L"ItemContents_Name");
		contents->AddComponent<CanvasRenderer>();
		contents->AddComponent<Text>(&desc);
		contents->SetScale(200.f, 25.f);
		return contents;
	}

	// bar

	static GameObject* Prefab_ItemExplane(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		Text::Desc desc;
		desc.width = 12;
		desc.height = 24;
		desc.text = _text;
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		auto script = INSTANTIATE(OBJECT_TAG_UI, L"Script");
		script->AddComponent<CanvasRenderer>();
		script->AddComponent<Text>(&desc);
		script->SetScale(760.f, 150.f);

		return script;
	}
	static GameObject* Prefab_KeyHelper(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		
	}

	static GameObject* Prefab_ItemContents_Bar(const float* _targetValue, float _max, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		auto bar = INSTANTIATE();

		auto background = CreateImage(_group, L"niniz");
		background->SetPosition(0.f, 0.f, 0.f);
		background->SetScale(160.f, 25.f);
		auto fill = CreateImage(_group, L"UIRed");
		fill->SetPosition(0.f, 0.f, 0.f);
		fill->SetScale(160.f, 25.f);

		Slider::Desc desc;
		desc.background = background->GetTransform();
		desc.fill = fill->GetTransform();
		desc.targetValue = _targetValue;
		desc.maxValue = _max;

		bar->AddComponent<CanvasRenderer>();
		bar->AddComponent<Slider>(&desc);
		
		background->SetParents(bar);
		fill->SetParents(bar);

		return bar;
	}
public:
	static GameObject* CreateEditController()
	{
		auto controller = INSTANTIATE();
		controller->AddComponent<EditController>();

		return controller;
	}
};

#endif // !__UIFACTORY_H__
