#pragma once
#ifndef __UILABSCENE_H__
#define __UILABSCENE_H__

#include "PlayerInfoManager.h"
#include "Scene.h"
class UILabScene :
	public Scene
{

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;

public:
	void CreatePauseButton();

	void CreateRader();

	void CreateSplineCurve();

	void PlayerUIPatitial();

	static void GarageMainWindow()
	{
		// reference
		{
			SingleImage::Desc desc_si;
			desc_si.textureName = L"garageSample";
			auto background = INSTANTIATE();
			background->AddComponent<CanvasRenderer>();
			background->AddComponent<SingleImage>(&desc_si);
			background->GetComponent<CanvasRenderer>()->SetFade(0.1f);
			background->SetPosition(WINCX * 0.5f, WINCY * 0.5f);
			background->SetScale(WINCX, WINCY);
		}

		// Menu
		{
			// Title (text)
			{
				auto title = UIFactory::Prefab_MenuTitle(L"MAIN MENU", CANVAS_GROUP_MAINWND);
				title->SetPosition(576.f, 124.f);
			}

			// Menu 1 - START STAGE	(Button)
			{
				EventHandler eventFunc = EventHandler([=]() {});
				auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"START STAGE", CANVAS_GROUP_MAINWND);
				menu->SetPosition(576.f, 230.f);
			}
			// Menu 2 - WEAPON (Button)
			{
				EventHandler eventFunc = EventHandler([=]() {});
				auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"SELECT WEAPON", CANVAS_GROUP_MAINWND);
				menu->SetPosition(576.f, 270.f);
			}
			// Menu 3 - SKILL (Button)
			{
				EventHandler eventFunc = EventHandler([=]() {});
				auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"SELECT SKILL", CANVAS_GROUP_MAINWND);
				menu->SetPosition(576.f, 310.f);
			}
			// Menu 4 - STAGE SELECT (Button)
			{
				EventHandler eventFunc = EventHandler([=]() {});
				auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"RETURN TO MAP", CANVAS_GROUP_MAINWND);
				menu->SetPosition(576.f, 350.f);
			}
		}
		// description (text)
		{
			auto script = UIFactory::Prefab_ItemExplane(L"이곳은 아마 선택한 기체에 대해 설명하는 곳입니다. 그런데 줄바꿈 문제없이 되나요???????", CANVAS_GROUP_MAINWND);
			script->SetPosition(576.f, 880.f);
		}


		// key helper (image)
		// key helper text (text)

		// player info
		{
			// ItemTitle
			{
				auto title = UIFactory::Prefab_ItemTitle(L"AIRCRAFT NAME");
				title->SetPosition(1640.f, 195.f);
			}
			// ItemSubtitle
			{
				auto subtitle = UIFactory::Prefab_ItemSubtitle(L"[Description about item]");
				subtitle->SetPosition(1640.f, 230.f);
			}
			// Item Contents
			{
				// attack
				// defence
				// hp
				// speed
				// guitar
				auto info = PlayerInfoManager::GetInstance();
				// speed
				{
					auto name = UIFactory::Prefab_ItemContents_Name(L"SPEED");
					name->SetPosition(1555.f, 260.f);

					const float* valueRef = &info->GetMaxSpeed();
					//wstring value = to_wstring(info->GetMaxSpeed());

					//auto bar = UIFactory::Prefab_ItemContents_Name(value);
					//bar->SetPosition(1740.f, 260.f);
					auto bar = UIFactory::Prefab_ItemContents_Bar(valueRef, 50.f, CANVAS_GROUP_MAINWND);
					bar->SetPosition(1740.f, 260.f);
				}

				//c3
				{
					auto name = UIFactory::Prefab_ItemContents_Name(L"DURABILITY");
					name->SetPosition(1555.f, 290.f);

					wstring value = to_wstring(info->GetMaxHp());
					auto bar = UIFactory::Prefab_ItemContents_Name(value);
					bar->SetPosition(1740.f, 290.f);
				}

				//c1
				{
					auto name = UIFactory::Prefab_ItemContents_Name(L"ATTACK");
					name->SetPosition(1555.f, 320.f);

					wstring value = to_wstring(info->GetAttack());
					auto bar = UIFactory::Prefab_ItemContents_Name(value);
					bar->SetPosition(1740.f, 320.f);
				}

				//c2
				{
					auto name = UIFactory::Prefab_ItemContents_Name(L"DEFENCE");
					name->SetPosition(1555.f, 350.f);

					wstring value = to_wstring(info->GetDirSenser());
					auto bar = UIFactory::Prefab_ItemContents_Name(value);
					bar->SetPosition(1740.f, 350.f);
				}

				//c3
				{
					auto name = UIFactory::Prefab_ItemContents_Name(L"ADDITIANAL");
					name->SetPosition(1555.f, 380.f);

					wstring value = to_wstring(info->GetMinSpeed());
					auto bar = UIFactory::Prefab_ItemContents_Name(value);
					bar->SetPosition(1740.f, 380.f);
				}
			}
		}
	}
};



#endif // !__UILABSCENE_H__

