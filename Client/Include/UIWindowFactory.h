#pragma once
#ifndef __UIWINDOWNFACTORY_H__
#define __UIWINDOWNFACTORY_H__

#include "Core.h"
#include "UIFactory.h"

#include "PlayerInfoManager.h"
#include "PlayerKitSelector.h"
#include "UIInteractor.h"
#include "Scripter.h"
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

				SetFloatFunc setValueFunc =
					SetFloatFunc([=](float* _out, GetFloatFunc _func) {
					*_out = _func();
				});

				// speed
				{
					auto name = UIFactory::Prefab_ItemContents_Name(L"SPEED");
					name->SetPosition(1555.f, 260.f);


					GetFloatFunc getValueFunc =
						GetFloatFunc([=]() {
						return (float)PlayerInfoManager::GetInstance()->GetMaxSpeed();
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
						return (float)PlayerInfoManager::GetInstance()->GetMaxHp();
					});

					auto bar = UIFactory::Prefab_ItemContents_Bar(CANVAS_GROUP_MAINWND);
					EventHandler eventFunc =
						EventHandler([=]() {
						bar->GetComponent<Slider>()->UpdateFillAmount(setValueFunc, getValueFunc);
					});

					_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc);
					bar->SetPosition(1740.f, 290.f);
				}

				//c3
				{
					auto name = UIFactory::Prefab_ItemContents_Name(L"ATTACK");
					name->SetPosition(1555.f, 320.f);

					GetFloatFunc getValueFunc =
						GetFloatFunc([=]() {
						return (float)PlayerInfoManager::GetInstance()->GetAttack();
					});

					auto bar = UIFactory::Prefab_ItemContents_Bar(CANVAS_GROUP_MAINWND);
					EventHandler eventFunc =
						EventHandler([=]() {
						bar->GetComponent<Slider>()->UpdateFillAmount(setValueFunc, getValueFunc);
					});

					_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc); 
					
					bar->SetPosition(1740.f, 320.f);
				}

				//c4
				{
					auto name = UIFactory::Prefab_ItemContents_Name(L"DEFENCE");
					name->SetPosition(1555.f, 350.f);

					GetFloatFunc getValueFunc =
						GetFloatFunc([=]() {
						return (float)PlayerInfoManager::GetInstance()->GetAttack();
					});

					auto bar = UIFactory::Prefab_ItemContents_Bar(CANVAS_GROUP_MAINWND);
					EventHandler eventFunc =
						EventHandler([=]() {
						bar->GetComponent<Slider>()->UpdateFillAmount(setValueFunc, getValueFunc);
					});

					_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc); 
					
					bar->SetPosition(1740.f, 350.f);
				}

				//c5
				{
					auto name = UIFactory::Prefab_ItemContents_Name(L"ADDITIANAL");
					name->SetPosition(1555.f, 380.f);


					GetFloatFunc getValueFunc =
						GetFloatFunc([=]() {
						return (float)PlayerInfoManager::GetInstance()->GetAttack();
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

	static void DogfightStageWindow(GameObject* _player)
	{
		// reference
		{
			SingleImage::Desc desc_si;
			desc_si.textureName = L"smog";
			auto background = INSTANTIATE();
			background->AddComponent<CanvasRenderer>();
			background->AddComponent<SingleImage>(&desc_si);
			background->GetComponent<CanvasRenderer>()->SetFade(0.6f);
			background->SetPosition(WINCX * 0.5f, WINCY * 0.5f);
			background->SetScale(WINCX, WINCY);
		}

		// stage info
		{

			SetFloatFunc setValueFunc =
				SetFloatFunc([=](float* _out, GetFloatFunc _func) {
				*_out = _func();
			});


			// time limit
			{
				// text
				auto timeText = UIFactory::Prefab_StageInfo_TimeText(L"TIME", CANVAS_GROUP_STAGEWND);
				timeText->SetPosition(140.f, 70.f);

				// value;

				auto timeNumber = UIFactory::Prefab_StageInfo_TimeNumber(CANVAS_GROUP_STAGEWND);
				timeNumber->SetPosition(230.f, 70.f);


				GetFloatFunc getValueFunc =
					GetFloatFunc([=]() {
					return PlayerInfoManager::GetInstance()->GetTimeLimit();
				});
				EventHandler eventFunc =
					EventHandler([=]() {
					timeNumber->GetComponent<Number>()->UpdateValue(setValueFunc, getValueFunc);
				});
				
				_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc);
			}
			// score
			{
				// text
				auto scoreText = UIFactory::Prefab_StageInfo_ScoreText(L"SCORE", CANVAS_GROUP_STAGEWND);
				scoreText->SetPosition(150.f, 105.f);

				// value;

				auto scoreNumber = UIFactory::Prefab_StageInfo_ScoreNumber(CANVAS_GROUP_STAGEWND);
				scoreNumber->SetPosition(250.f, 105.f);


				GetFloatFunc getValueFunc =
					GetFloatFunc([=]() {
					return PlayerInfoManager::GetInstance()->GetScore();
				});
				
				EventHandler eventFunc =
					EventHandler([=]() {
					scoreNumber->GetComponent<Number>()->UpdateValue(setValueFunc, getValueFunc);
				});

				_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc);
			}
			// target
			{
				// text
				auto targetText = UIFactory::Prefab_StageInfo_TargetText(L"TARGET", CANVAS_GROUP_STAGEWND);
				targetText->SetPosition(160.f, 140.f);

				// name

				/*auto scoreNumber = UIFactory::Prefab_StageInfo_TimeNumber(CANVAS_GROUP_STAGEWND);
				scoreNumber->SetPosition(246.f, 105.f);


				GetFloatFunc getValueFunc =
					GetFloatFunc([=]() {
					return PlayerInfoManager::GetInstance()->GetScore();
				});

				EventHandler eventFunc =
					EventHandler([=]() {
					scoreNumber->GetComponent<Number>()->UpdateValue(setValueFunc, getValueFunc);
				});

				_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc);*/
			}

		}
		// Scripter
		DogfightScript();

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

	static void DogfightScript()
	{
		// dialogue title
		auto titleText = UIFactory::Prefab_Stage_DialogueTitle(L"");
		titleText->SetPosition(960.f, 60.f);
		// dialogue script
		auto scriptText = UIFactory::Prefab_Stage_DialogueScript(L"");
		scriptText->SetPosition(960.f, 120.f);
		// sample script
		vector<Dialogue> list;
		{
			wstring title = L"전근희";
			wstring script = L"<< 행님들 제가 생각을 해봤는데 말이죠 >>";

			Dialogue dialogue;
			dialogue.first = title;
			dialogue.second = script;

			list.emplace_back(dialogue);

			script = L"<< 이거 어떻게 동작하는 거에요? >>";
			dialogue.second = script;
			list.emplace_back(dialogue);
			script = L"<< 아 이라면 돼요? >>";
			dialogue.second = script;
			list.emplace_back(dialogue);
			script = L"<< 크... 오늘도 하나 배워 갑니다. >>";
			dialogue.second = script;
			list.emplace_back(dialogue);
			script = L"<< 어라..? 이렇게 쉽게 이해하는 나, 사실은 이 팀 에이스 일 지도..? >>";
			dialogue.second = script;
			list.emplace_back(dialogue);
		}
		// scripter
		Scripter::Desc desc_scr;
		desc_scr.title = titleText->GetComponent<Text>();
		desc_scr.script = scriptText->GetComponent<Text>();
		desc_scr.startDialogue = list;
		auto scripter =
			INSTANTIATE()->
			AddComponent<Scripter>(&desc_scr);
	}
};



#endif // !__UIWINDOWNFACTORY_H__
