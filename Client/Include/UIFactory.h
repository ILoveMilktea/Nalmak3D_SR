#pragma once
#ifndef __UIFACTORY_H__
#define __UIFACTORY_H__

#include "stdafx.h"

#include "Core.h"
#include "Rader.h"
#include "Crosshair.h"
#include "EditController.h"
#include "PlayerInfoManager.h"
#include "EnemyDetector.h"
#include "BossUIAnimator.h"
#include "ItemButton.h"

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

#pragma region MainMenu
	static GameObject* Prefab_MenuTitle(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc;
		desc.width = 12;
		desc.height = 30;
		desc.text = _text;
		desc.color = D3DCOLOR_RGBA(50, 200, 250, 255);
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		auto text = INSTANTIATE(OBJECT_TAG_UI, L"MenuTitle");
		text->AddComponent<CanvasRenderer>(&desc_cr);
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
		desc.color = D3DCOLOR_RGBA(50, 200, 250, 255);
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		menu->AddComponent<Text>(&desc);

		menu->SetScale(760.f, 30.f);
		return menu;
	}
	static GameObject* Prefab_ItemMenuButton(EventHandler _eventFunc, const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// button
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Button::Desc desc_bt;
		desc_bt.eventFunc = _eventFunc;

		ItemButton::Desc desc_ib;
		desc_ib.desc_button = desc_bt;

		auto menu = INSTANTIATE(OBJECT_TAG_UI, L"ItemMenuButton");
		menu->AddComponent<CanvasRenderer>(&desc_cr);
		menu->AddComponent<ItemButton>(&desc_ib);

		menu->GetComponent<ItemButton>()->ChangeNormalColor(1.f, 1.f, 1.f, 0.f);
		menu->GetComponent<ItemButton>()->ChangeHighlightColor(0.f, 0.5f, 0.8f, 0.5f);
		menu->GetComponent<ItemButton>()->ChangePressedColor(0.9f, 0.6f, 0.f, 0.5f);
		menu->GetComponent<ItemButton>()->ChangeDisableColor(0.2f, 0.2f, 0.2f, 0.5f);

		// text
		Text::Desc desc;
		desc.width = 10;
		desc.height = 25;
		desc.text = _text;
		desc.color = D3DCOLOR_RGBA(50, 200, 250, 255);
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		menu->AddComponent<Text>(&desc);

		menu->SetScale(760.f, 30.f);
		return menu;
	}

	static GameObject* Prefab_ItemTitle(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc;
		desc.width = 10;
		desc.height = 25;
		desc.text = _text;
		desc.color = D3DCOLOR_RGBA(50, 200, 250, 255);
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		auto subtitle = INSTANTIATE(OBJECT_TAG_UI, L"ItemTitle");
		subtitle->AddComponent<CanvasRenderer>(&desc_cr);
		subtitle->AddComponent<Text>(&desc);
		subtitle->SetScale(380.f, 30.f);
		return subtitle;
	}
	static GameObject* Prefab_ItemSubtitle(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc;
		desc.width = 8;
		desc.height = 20;
		desc.text = _text;
		desc.color = D3DCOLOR_RGBA(50, 200, 250, 255);
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		auto subtitle = INSTANTIATE(OBJECT_TAG_UI, L"ItemSubtitle");
		subtitle->AddComponent<CanvasRenderer>(&desc_cr);
		subtitle->AddComponent<Text>(&desc);
		subtitle->SetScale(380.f, 25.f);
		return subtitle;
	}
	static GameObject* Prefab_ItemContents_Name(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc;
		desc.width = 10;
		desc.height = 25;
		desc.text = _text;
		desc.color = D3DCOLOR_RGBA(50, 200, 250, 255);
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		auto contents = INSTANTIATE(OBJECT_TAG_UI, L"ItemContents_Name");
		contents->AddComponent<CanvasRenderer>(&desc_cr);
		contents->AddComponent<Text>(&desc);
		contents->SetScale(200.f, 25.f);
		return contents;
	}

	// bar

	static GameObject* Prefab_ItemExplane(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc;
		desc.width = 12;
		desc.height = 24;
		desc.text = _text;
		desc.color = D3DCOLOR_RGBA(50, 200, 250, 255);
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		auto script = INSTANTIATE(OBJECT_TAG_UI, L"Script");
		script->AddComponent<CanvasRenderer>(&desc_cr);
		script->AddComponent<Text>(&desc);
		script->SetScale(760.f, 150.f);

		return script;
	}
	static GameObject* Prefab_KeyHelper(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{

	}

	static GameObject* Prefab_ItemContents_Bar(CANVAS_GROUP _group = CANVAS_GROUP_NONE, float _maxValue = 100.f, float _minValue = 0.f)
	{
		auto bar = INSTANTIATE();

		auto background = CreateImage(_group, L"niniz");
		background->SetPosition(0.f, 0.f, 0.f);
		background->SetScale(160.f, 25.f);
		auto fill = CreateImage(_group, L"UIRed");
		fill->SetPosition(0.f, 0.f, 0.f);
		fill->SetScale(152.f, 21.f);

		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Slider::Desc desc;
		desc.background = background->GetTransform();
		desc.fill = fill->GetTransform();
		desc.maxValue = _maxValue;
		desc.minValue = _minValue;

		bar->AddComponent<CanvasRenderer>(&desc_cr);
		bar->AddComponent<Slider>(&desc);

		bar->GetComponent<Slider>()->SetCurrentValue(_maxValue);

		background->SetParents(bar);
		fill->SetParents(bar);

		return bar;
	}
#pragma endregion

public:

#pragma region StageUI
	static GameObject* Prefab_Stage_TimeText(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc;
		desc.width = 12;
		desc.height = 30;
		desc.text = _text;
		desc.color = D3DCOLOR_RGBA(25, 255, 25, 255);
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		auto text = INSTANTIATE(OBJECT_TAG_UI, L"Stage_TimeText");
		text->AddComponent<CanvasRenderer>(&desc_cr);
		text->AddComponent<Text>(&desc);
		text->SetScale(60.f, 30.f);
		return text;
	}
	static GameObject* Prefab_Stage_TimeNumber(CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc_text;
		desc_text.width = 12;
		desc_text.height = 30;
		desc_text.text = L"0";
		desc_text.color = D3DCOLOR_RGBA(25, 255, 25, 255);
		desc_text.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		Number::Desc desc_num;
		desc_num.text_desc = desc_text;
		desc_num.printType = Number::TIME_M_S_MS;

		auto number = INSTANTIATE(OBJECT_TAG_UI, L"Stage_TimeNumber");
		number->AddComponent<CanvasRenderer>(&desc_cr);
		number->AddComponent<Number>(&desc_num);
		number->SetScale(120.f, 30.f);
		return number;
	}

	static GameObject* Prefab_Stage_ScoreText(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc;
		desc.width = 12;
		desc.height = 30;
		desc.text = _text;
		desc.color = D3DCOLOR_RGBA(25, 255, 25, 255);
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		auto text = INSTANTIATE(OBJECT_TAG_UI, L"Stage_ScoreText");
		text->AddComponent<CanvasRenderer>(&desc_cr);
		text->AddComponent<Text>(&desc);
		text->SetScale(84.f, 30.f);
		return text;
	}
	static GameObject* Prefab_Stage_ScoreNumber(CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc_text;
		desc_text.width = 12;
		desc_text.height = 30;
		desc_text.text = L"0";
		desc_text.color = D3DCOLOR_RGBA(25, 255, 25, 255);
		desc_text.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		Number::Desc desc_num;
		desc_num.text_desc = desc_text;
		desc_num.printType = Number::NUMBER;

		auto number = INSTANTIATE(OBJECT_TAG_UI, L"Stage_ScoreNumber");
		number->AddComponent<CanvasRenderer>(&desc_cr);
		number->AddComponent<Number>(&desc_num);
		number->SetScale(110.f, 30.f);
		return number;
	}

	static GameObject* Prefab_Stage_TargetText(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc;
		desc.width = 12;
		desc.height = 30;
		desc.text = _text;
		desc.color = D3DCOLOR_RGBA(25, 255, 25, 255);
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		auto text = INSTANTIATE(OBJECT_TAG_UI, L"Stage_TargetText");
		text->AddComponent<CanvasRenderer>(&desc_cr);
		text->AddComponent<Text>(&desc);
		text->SetScale(100.f, 30.f);
		return text;
	}
	static GameObject* Prefab_Stage_TargetName(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		//Text::Desc desc;
		//desc.width = 12;
		//desc.height = 30;
		//desc.text = _text;
		//desc.color = D3DCOLOR_RGBA(25, 255, 25, 255);
		//desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		//auto text = INSTANTIATE(OBJECT_TAG_UI, L"Stage_TargetText");
		//text->AddComponent<CanvasRenderer>();
		//text->AddComponent<Text>(&desc);
		//text->SetScale(100.f, 30.f);
		//return text;
	}

	static GameObject* Prefab_Stage_DialogueTitle(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc;
		desc.width = 12;
		desc.height = 30;
		desc.weight = 800;
		desc.text = _text;
		desc.color = D3DCOLOR_RGBA(50, 100, 255, 255);
		desc.option = DT_CENTER | DT_WORDBREAK | DT_VCENTER;

		auto text = INSTANTIATE(OBJECT_TAG_UI, L"Stage_TargetText");
		text->AddComponent<CanvasRenderer>(&desc_cr);
		text->AddComponent<Text>(&desc);
		text->SetScale(640.f, 36.f);
		return text;
	}
	static GameObject* Prefab_Stage_DialogueScript(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc;
		desc.width = 12;
		desc.height = 30;
		desc.weight = 700;
		desc.text = _text;
		desc.color = D3DCOLOR_RGBA(225, 225, 225, 255);
		desc.option = DT_CENTER | DT_WORDBREAK | DT_VCENTER;

		auto text = INSTANTIATE(OBJECT_TAG_UI, L"Stage_TargetText");
		text->AddComponent<CanvasRenderer>(&desc_cr);
		text->AddComponent<Text>(&desc);
		text->SetPosition(960.f, 120.f);
		text->SetScale(640.f, 72.f);
		return text;
	}

	static GameObject* Prefab_Stage_SpeedText(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc;
		desc.width = 12;
		desc.height = 30;
		desc.text = _text;
		desc.color = D3DCOLOR_RGBA(25, 255, 25, 255);
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		auto text = INSTANTIATE(OBJECT_TAG_UI, L"Stage_TimeText");
		text->AddComponent<CanvasRenderer>(&desc_cr);
		text->AddComponent<Text>(&desc);
		text->SetScale(110.f, 40.f);
		return text;
	}
	static GameObject* Prefab_Stage_SpeedNumber(CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// Number
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc_text;
		desc_text.width = 12;
		desc_text.height = 30;
		desc_text.text = L"0";
		desc_text.color = D3DCOLOR_RGBA(25, 255, 25, 255);
		desc_text.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		Number::Desc desc_num;
		desc_num.text_desc = desc_text;
		desc_num.printType = Number::NUMBER;

		auto number = INSTANTIATE(OBJECT_TAG_UI, L"Stage_SpeedNumber");
		number->AddComponent<CanvasRenderer>(&desc_cr);
		number->AddComponent<Number>(&desc_num);
		number->SetScale(110.f, 40.f);

		return number;
	}

	static GameObject* Prefab_Stage_Crosshair(CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		SingleImage::Desc desc_img;
		desc_img.textureName = L"crosshair";

		Crosshair::Desc desc_ch;
		desc_ch.img_desc = desc_img;

		auto crosshair = INSTANTIATE()->
			AddComponent<CanvasRenderer>(&desc_cr)->
			AddComponent<Crosshair>(&desc_ch);

		crosshair->SetScale(64.f, 64.f);
		
		return crosshair;

	}


	static GameObject* Prefab_Stage_AltitudeText(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc;
		desc.width = 12;
		desc.height = 30;
		desc.text = _text;
		desc.color = D3DCOLOR_RGBA(25, 255, 25, 255);
		desc.option = DT_RIGHT | DT_WORDBREAK | DT_VCENTER;

		auto text = INSTANTIATE(OBJECT_TAG_UI, L"Stage_AltText");
		text->AddComponent<CanvasRenderer>(&desc_cr);
		text->AddComponent<Text>(&desc);
		text->SetScale(110.f, 40.f);
		return text;
	}
	static GameObject* Prefab_Stage_AltitudeNumber(CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// Number
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc_text;
		desc_text.width = 12;
		desc_text.height = 30;
		desc_text.text = L"0";
		desc_text.color = D3DCOLOR_RGBA(25, 255, 25, 255);
		desc_text.option = DT_RIGHT | DT_WORDBREAK | DT_VCENTER;

		Number::Desc desc_num;
		desc_num.text_desc = desc_text;
		desc_num.printType = Number::NUMBER;

		auto number = INSTANTIATE(OBJECT_TAG_UI, L"Stage_AltNumber");
		number->AddComponent<CanvasRenderer>(&desc_cr);
		number->AddComponent<Number>(&desc_num);
		number->SetScale(110.f, 40.f);

		return number;
	}
	
	static GameObject* Prefab_Stage_PlayerInfoText(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// text
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc;
		desc.width = 12;
		desc.height = 30;
		desc.text = _text;
		desc.color = D3DCOLOR_RGBA(25, 255, 25, 255);
		desc.option = DT_LEFT | DT_WORDBREAK | DT_VCENTER;

		auto text = INSTANTIATE(OBJECT_TAG_UI, L"Stage_PlayerInfoText");
		text->AddComponent<CanvasRenderer>(&desc_cr);
		text->AddComponent<Text>(&desc);
		text->SetScale(96.f, 36.f);
		return text;
	}

	static GameObject* Prefab_Stage_PlayerInfoBar(CANVAS_GROUP _group = CANVAS_GROUP_NONE, float _maxValue = 100.f, float _minValue = 0.f)
	{
		auto bar = INSTANTIATE();

		auto background = CreateImage(_group, L"boundary");
		background->SetPosition(0.f, 0.f);
		background->SetScale(80.f, 36.f);
		auto fill = CreateImage(_group, L"UIGreen");
		fill->SetPosition(0.f, 0.f);
		fill->SetScale(70.f, 28.f);

		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Slider::Desc desc;
		desc.background = background->GetTransform();
		desc.fill = fill->GetTransform();
		desc.maxValue = _maxValue;
		desc.minValue = _minValue;

		bar->AddComponent<CanvasRenderer>(&desc_cr);
		bar->AddComponent<Slider>(&desc);

		bar->GetComponent<Slider>()->SetCurrentValue(_maxValue);

		background->SetParents(bar);
		fill->SetParents(bar);

		return bar;
	}

	static GameObject* Prefab_Stage_PlayerInfoNumber(CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// Number
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc_text;
		desc_text.width = 12;
		desc_text.height = 30;
		desc_text.text = L"0";
		desc_text.color = D3DCOLOR_RGBA(25, 255, 25, 255);
		desc_text.option = DT_RIGHT | DT_WORDBREAK | DT_VCENTER;

		Number::Desc desc_num;
		desc_num.text_desc = desc_text;
		desc_num.printType = Number::NUMBER;

		auto number = INSTANTIATE(OBJECT_TAG_UI, L"Stage_PlayerInfoNumber");
		number->AddComponent<CanvasRenderer>(&desc_cr);
		number->AddComponent<Number>(&desc_num);
		number->SetScale(60.f, 36.f);

		return number;
	}

	static GameObject* Prefab_Rader(CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		// rader
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Rader::Desc desc;
		desc.findRange = 200.f;
		desc.readyIcon = 10;

		auto rader = INSTANTIATE()->
			AddComponent<CanvasRenderer>(&desc_cr)->
			AddComponent<Rader>(&desc);
		
		return rader;
	}

	static GameObject* Prefab_EnemyDetector(GameObject* _crosshair, CANVAS_GROUP _group = CANVAS_GROUP_NONE)
	{
		auto boundary = CreateImage(_group, L"detectorBoundary");
		boundary->SetPosition(WINCX * 0.5f, WINCY *0.5f);
		boundary->SetScale(480.f, 480.f);
		boundary->GetComponent<CanvasRenderer>()->SetFade(0.3f);

		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		EnemyDetector::Desc desc_ed;
		desc_ed.crosshair = _crosshair;

		auto enemyDetector = INSTANTIATE(OBJECT_TAG_UI, L"detector")->
			AddComponent<CanvasRenderer>(&desc_cr)->
			AddComponent<EnemyDetector>(&desc_ed);

		return enemyDetector;
	}
#pragma endregion

public:
	static GameObject* Prefab_Stage_BossName(const wstring& _text, CANVAS_GROUP _group = CANVAS_GROUP_BOSSHP)
	{
		// text
		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Text::Desc desc;
		desc.width = 20;
		desc.height = 40;
		desc.text = _text;		
		desc.color = D3DCOLOR_RGBA(255, 255, 255, 255);
		desc.option = DT_CENTER | DT_WORDBREAK | DT_VCENTER;

		auto text = INSTANTIATE(OBJECT_TAG_UI, L"Stage_BossName");
		text->AddComponent<CanvasRenderer>(&desc_cr);
		text->AddComponent<Text>(&desc);
		text->SetScale(480.f, 50.f);

		text->AddComponent<BossUIAnimator>();
		return text;
	}

	static GameObject* Prefab_Stage_BossHpSlider(CANVAS_GROUP _group = CANVAS_GROUP_BOSSHP, float _maxValue = 100.f, float _minValue = 0.f)
	{
		auto slider = INSTANTIATE();

		auto background = CreateImage(_group, L"UIWhite");
		background->SetPosition(0.f, 0.f);
		background->SetScale(960.f, 40.f);
		auto fill = CreateImage(_group, L"UIGreen");
		fill->SetPosition(0.f, 0.f);
		fill->SetScale(940.f, 32.f);

		CanvasRenderer::Desc desc_cr;
		desc_cr.group = _group;

		Slider::Desc desc;
		desc.background = background->GetTransform();
		desc.fill = fill->GetTransform();
		desc.maxValue = _maxValue;
		desc.minValue = _minValue;

		slider->AddComponent<CanvasRenderer>(&desc_cr);
		slider->AddComponent<Slider>(&desc);
		slider->AddComponent<BossUIAnimator>();

		slider->GetComponent<Slider>()->SetCurrentValue(_maxValue);

		background->SetParents(slider);
		fill->SetParents(slider);

		return slider;
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