#pragma once
#ifndef __UIWINDOWNFACTORY_H__
#define __UIWINDOWNFACTORY_H__

#include "Core.h"
#include "UIFactory.h"

#include "PlayerInfoManager.h"
#include "PlayerKitSelector.h"
#include "UIInteractor.h"
class UIWindowFactory
{
public:

	static void GarageMainWindow(GameObject* _player)
	{
		auto interactiveController = INSTANTIATE();

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
				EventHandler eventFunc = EventHandler([=]() {
					Core::GetInstance()->LoadScene(L"phantom");
				});
				auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"START STAGE", CANVAS_GROUP_MAINWND);
				menu->SetPosition(576.f, 230.f);
			}
			// Menu 2 - WEAPON (Button)
			{
				EventHandler eventFunc = EventHandler([]() {
					ItemDesc * ItemDescInfo = PlayerKitSelector::GetInstance()->FindSlotItme(L"Weapon", ITEMTYPE::ITEMTYPE_CANNON);
					PlayerInfoManager::GetInstance()->EquipWepon(PARTS_NUM::FIRST_PARTS, ItemDescInfo);

				});

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


					GetFloatFunc getValueFunc =
						GetFloatFunc([=]() {
						return PlayerInfoManager::GetInstance()->GetMaxSpeed();
					});

					SetFloatFunc setValueFunc =
						SetFloatFunc([=](float* _out, GetFloatFunc _func) {
						*_out = _func();
					});

					auto bar = UIFactory::Prefab_ItemContents_Bar(CANVAS_GROUP_MAINWND);
					EventHandler eventFunc =
						EventHandler([=]() {
						bar->GetComponent<Slider>()->UpdateFillAmount(setValueFunc, getValueFunc);
					});

					_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc);
					bar->SetPosition(1740.f, 260.f);
				}

				//c3
				{
					auto name = UIFactory::Prefab_ItemContents_Name(L"DURABILITY");
					name->SetPosition(1555.f, 290.f);

					GetFloatFunc getValueFunc =
						GetFloatFunc([=]() {
						return PlayerInfoManager::GetInstance()->GetMaxHp();
					});

					SetFloatFunc setValueFunc =
						SetFloatFunc([=](float* _out, GetFloatFunc _func) {
						*_out = _func();
					});

					auto bar = UIFactory::Prefab_ItemContents_Bar(CANVAS_GROUP_MAINWND);
					EventHandler eventFunc =
						EventHandler([=]() {
						bar->GetComponent<Slider>()->UpdateFillAmount(setValueFunc, getValueFunc);
					});

					_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc);
					bar->SetPosition(1740.f, 290.f);
				}

				//c1
				{
					auto name = UIFactory::Prefab_ItemContents_Name(L"ATTACK");
					name->SetPosition(1555.f, 320.f);

					GetFloatFunc getValueFunc =
						GetFloatFunc([=]() {
						return PlayerInfoManager::GetInstance()->GetAttack();
					});

					SetFloatFunc setValueFunc =
						SetFloatFunc([=](float* _out, GetFloatFunc _func) {
						*_out = _func();
					});

					auto bar = UIFactory::Prefab_ItemContents_Bar(CANVAS_GROUP_MAINWND);
					EventHandler eventFunc =
						EventHandler([=]() {
						bar->GetComponent<Slider>()->UpdateFillAmount(setValueFunc, getValueFunc);
					});

					_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc); 
					
					bar->SetPosition(1740.f, 320.f);
				}

				//c2
				{
					auto name = UIFactory::Prefab_ItemContents_Name(L"DEFENCE");
					name->SetPosition(1555.f, 350.f);

					GetFloatFunc getValueFunc =
						GetFloatFunc([=]() {
						return PlayerInfoManager::GetInstance()->GetAttack();
					});

					SetFloatFunc setValueFunc =
						SetFloatFunc([=](float* _out, GetFloatFunc _func) {
						*_out = _func();
					});

					auto bar = UIFactory::Prefab_ItemContents_Bar(CANVAS_GROUP_MAINWND);
					EventHandler eventFunc =
						EventHandler([=]() {
						bar->GetComponent<Slider>()->UpdateFillAmount(setValueFunc, getValueFunc);
					});

					_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc); 
					
					bar->SetPosition(1740.f, 350.f);
				}

				//c3
				{
					auto name = UIFactory::Prefab_ItemContents_Name(L"ADDITIANAL");
					name->SetPosition(1555.f, 380.f);


					GetFloatFunc getValueFunc =
						GetFloatFunc([=]() {
						return PlayerInfoManager::GetInstance()->GetAttack();
					});

					SetFloatFunc setValueFunc =
						SetFloatFunc([=](float* _out, GetFloatFunc _func) {
						*_out = _func();
					});

					auto bar = UIFactory::Prefab_ItemContents_Bar(CANVAS_GROUP_MAINWND);
					EventHandler eventFunc =
						EventHandler([=]() {
						bar->GetComponent<Slider>()->UpdateFillAmount(setValueFunc, getValueFunc);
					});

					_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc); 
					
					bar->SetPosition(1740.f, 380.f);
				}
			}
		}
	}

	static void DogfightStageWindow()
	{
		// reference
		{
			SingleImage::Desc desc_si;
			desc_si.textureName = L"smog";
			auto background = INSTANTIATE();
			background->AddComponent<CanvasRenderer>();
			background->AddComponent<SingleImage>(&desc_si);
			background->GetComponent<CanvasRenderer>()->SetFade(0.4f);
			background->SetPosition(WINCX * 0.5f, WINCY * 0.5f);
			background->SetScale(WINCX, WINCY);
		}

		// stage info
		{

			// time limit
			{
				auto title = UIFactory::Prefab_StageInfo_TimeText(L"TIME", CANVAS_GROUP_STAGEWND);
				title->SetPosition(140.f, 70.f);
			}
			// score
			{
				auto title = UIFactory::Prefab_StageInfo_ScoreText(L"SCORE", CANVAS_GROUP_STAGEWND);
				title->SetPosition(150.f, 105.f);
			}
			// target
			{
				auto title = UIFactory::Prefab_StageInfo_TargetText(L"TARGET", CANVAS_GROUP_STAGEWND);
				title->SetPosition(160.f, 140.f);
			}

		}
		// alarm title
		// alarm script

		// speed text
		// speed box
		// speed value

		// speed text
		// speed box
		// speed value

		// alt text
		// alt value
		// alt box

		// rader
		{

			auto rader = UIFactory::Prefab_Rader(CANVAS_GROUP_STAGEWND);
			rader->SetPosition(250.f, 875.f);
		}

		// info
		//info value
		
	}

};



#endif // !__UIWINDOWNFACTORY_H__
