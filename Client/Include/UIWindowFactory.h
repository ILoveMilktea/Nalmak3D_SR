#pragma once
#ifndef __UIWINDOWNFACTORY_H__
#define __UIWINDOWNFACTORY_H__

#include "Core.h"
#include "UIFactory.h"

#include "PlayerInfoManager.h"
#include "UIInteractor.h"
#include "Scripter.h"
#include "ItemManager.h"

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
			// Menu 2 - WEAPON (Button) !!!!!!!!!!!!!TEST!!!!!!!!!!!!!
			{
				EventHandler eventFunc = EventHandler([=]() {

					ItemManager::GetInstance()->BuyItem(L"Weapon", L"AimMissile");

				});
				auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"(TEST)BUY WEAPON [ Weapon - AimMissile ] ", CANVAS_GROUP_MAINWND);
				menu->SetPosition(1600.f, 600.f);
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
			auto script = UIFactory::Prefab_ItemExplane(L"�̰��� �Ƹ� ������ ��ü�� ���� �����ϴ� ���Դϴ�. �׷��� �ٹٲ� �������� �ǳ���???????", CANVAS_GROUP_MAINWND);
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

				// SPEED
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

				// DURABILITY (HP)
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

				// ATTACK
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

				// DEFENCE
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

				// ���߿� �߰�
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

		SetFloatFunc setValueFunc =
			SetFloatFunc([=](float* _out, GetFloatFunc _func) {
			*_out = _func();
		});

		// stage info
		{

			// time limit
			{
				// text
				auto timeText = UIFactory::Prefab_Stage_TimeText(L"TIME", CANVAS_GROUP_STAGEWND);
				timeText->SetPosition(140.f, 70.f);

				// value;

				auto timeNumber = UIFactory::Prefab_Stage_TimeNumber(CANVAS_GROUP_STAGEWND);
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
				auto scoreText = UIFactory::Prefab_Stage_ScoreText(L"SCORE", CANVAS_GROUP_STAGEWND);
				scoreText->SetPosition(150.f, 105.f);

				// value;

				auto scoreNumber = UIFactory::Prefab_Stage_ScoreNumber(CANVAS_GROUP_STAGEWND);
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
				auto targetText = UIFactory::Prefab_Stage_TargetText(L"TARGET", CANVAS_GROUP_STAGE1);
				targetText->SetPosition(160.f, 140.f);

				// name

				/*auto scoreNumber = UIFactory::Prefab_Stage_TimeNumber(CANVAS_GROUP_STAGEWND);
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

		// speed
		{

			// speed text
			auto text = UIFactory::Prefab_Stage_SpeedText(L"SPEED", CANVAS_GROUP_STAGE1);
			text->SetPosition(650.f, 510.f);

			// box
			auto numberTag = UIFactory::CreateImage(CANVAS_GROUP_STAGE1, L"leftNumberTag");
			numberTag->SetScale(110.f, 40.f);
			numberTag->SetPosition(650.f, 540.f);
			// speed number
			{
				auto number = UIFactory::Prefab_Stage_SpeedNumber(CANVAS_GROUP_STAGE1);
				number->SetPosition(650.f, 540.f);

				GetFloatFunc getValueFunc =
					GetFloatFunc([=]() {
					return PlayerInfoManager::GetInstance()->GetSpeed();
				});

				EventHandler eventFunc =
					EventHandler([=]() {
					number->GetComponent<Number>()->UpdateValue(setValueFunc, getValueFunc);
				});


				_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc);
			}

		}

		// Crosshair
		{
			auto crosshair = UIFactory::Prefab_Stage_Crosshair(CANVAS_GROUP_STAGE1);
			crosshair->SetPosition(WINCX * 0.5f, WINCY * 0.5f);

			SetVector2Func setValueFunc =
				SetVector2Func([=](Vector2* _out, GetVector2Func _func) {
				*_out = _func();
			});

			GetVector2Func getValueFunc =
				GetVector2Func([=]() {
				return InputManager::GetInstance()->GetMouseScreenPos();
			});

			EventHandler eventFunc =
				EventHandler([=]() {
				crosshair->GetComponent<Crosshair>()->UpdatePosition(setValueFunc, getValueFunc);
			});


			_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc);
		}

		// altitude
		{

			// altitude text
			auto text = UIFactory::Prefab_Stage_AltitudeText(L"ALT", CANVAS_GROUP_STAGE1);
			text->SetPosition(1270.f, 510.f);

			// box
			auto numberTag = UIFactory::CreateImage(CANVAS_GROUP_STAGE1, L"rightNumberTag");
			numberTag->SetScale(110.f, 40.f);
			numberTag->SetPosition(1270.f, 540.f);
			// altitude number
			{
				auto number = UIFactory::Prefab_Stage_AltitudeNumber(CANVAS_GROUP_STAGE1);
				number->SetPosition(1270.f, 540.f);

				GetFloatFunc getValueFunc =
					GetFloatFunc([=]() {
					return 1000.f;
				});

				EventHandler eventFunc =
					EventHandler([=]() {
					number->GetComponent<Number>()->UpdateValue(setValueFunc, getValueFunc);
				});


				_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc);
			}

		}
		// rader
		{
			auto rader = UIFactory::Prefab_Rader(CANVAS_GROUP_STAGE1);
			rader->SetPosition(250.f, 875.f);
		}

		// Player Info
		{
			float interval = 36.f;
			// ==== sorted bottom -> top
			// Hp (slider)
			{
				// text
				auto name = UIFactory::Prefab_Stage_PlayerInfoText(L"HP");
				name->SetPosition(1700.f, 860.f);

				GetFloatFunc getValueFunc =
					GetFloatFunc([=]() {
					return (float)PlayerInfoManager::GetInstance()->GetHp();
				});

				// slider
				auto slider = UIFactory::Prefab_Stage_PlayerInfoBar(CANVAS_GROUP_STAGEWND);
				EventHandler eventFunc =
					EventHandler([=]() {
					slider->GetComponent<Slider>()->UpdateFillAmount(setValueFunc, getValueFunc);
				});
				slider->SetPosition(1768.f, 860.f);

				_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc);
			}
			// Skill 1 (number)
			{
				// text
				auto name = UIFactory::Prefab_Stage_PlayerInfoText(L"S2");
				name->SetPosition(1700.f, 860.f - interval);

				// number
				auto number = UIFactory::Prefab_Stage_PlayerInfoNumber(CANVAS_GROUP_STAGEWND);
				number->SetPosition(1780.f, 860.f - interval);

				GetFloatFunc getValueFunc =
					GetFloatFunc([=]() {
					return 5.f/* ���߿� skill ������? */;
				});

				EventHandler eventFunc =
					EventHandler([=]() {
					number->GetComponent<Number>()->UpdateValue(setValueFunc, getValueFunc);
				});


				_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc);

			}
			// skill 2
			{

				// text
				auto name = UIFactory::Prefab_Stage_PlayerInfoText(L"S1");
				name->SetPosition(1700.f, 860.f - interval * 2.f);

				// number
				auto number = UIFactory::Prefab_Stage_PlayerInfoNumber(CANVAS_GROUP_STAGEWND);
				number->SetPosition(1780.f, 860.f - interval * 2.f);

				GetFloatFunc getValueFunc =
					GetFloatFunc([=]() {
					return (float)PlayerInfoManager::GetInstance()->GetHp();
				});

				EventHandler eventFunc =
					EventHandler([=]() {
					number->GetComponent<Number>()->UpdateValue(setValueFunc, getValueFunc);
				});


				_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc);

			}
			// Weapon bullets? (number)
			{

				// text
				auto name = UIFactory::Prefab_Stage_PlayerInfoText(L"MSL");
				name->SetPosition(1700.f, 860.f - interval * 3.f);

				auto number = UIFactory::Prefab_Stage_PlayerInfoNumber(CANVAS_GROUP_STAGEWND);
				number->SetPosition(1780.f, 860.f - interval * 3.f);

				GetFloatFunc getValueFunc =
					GetFloatFunc([=]() {
					return 70.f /* bulletttt */;
				});

				EventHandler eventFunc =
					EventHandler([=]() {
					number->GetComponent<Number>()->UpdateValue(setValueFunc, getValueFunc);
				});


				_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc);

			}


			// skill img 1
			{
				auto img = UIFactory::CreateImage(CANVAS_GROUP_STAGEWND, L"boundary");
				img->SetScale(80.f, 80.f);
				img->SetPosition(1670.f, 960.f);
			}
			// skill img 2
			{
				auto img = UIFactory::CreateImage(CANVAS_GROUP_STAGEWND, L"boundary");
				img->SetScale(80.f, 80.f);
				img->SetPosition(1770.f, 960.f);
			}
		}

	}

	static void DogfightScript()
	{
		// dialogue title
		auto titleText = UIFactory::Prefab_Stage_DialogueTitle(L"", CANVAS_GROUP_STAGE1);
		titleText->SetPosition(960.f, 60.f);
		// dialogue script
		auto scriptText = UIFactory::Prefab_Stage_DialogueScript(L"", CANVAS_GROUP_STAGE1);
		scriptText->SetPosition(960.f, 120.f);
		// sample script
		vector<Dialogue> list;
		{
			wstring title = L"������";
			wstring script = L"<< ���Ե� ���� ������ �غôµ� ������ >>";

			Dialogue dialogue;
			dialogue.first = title;
			dialogue.second = script;

			list.emplace_back(dialogue);

			script = L"<< �̰� ��� �����ϴ� �ſ���? >>";
			dialogue.second = script;
			list.emplace_back(dialogue);
			script = L"<< �� �̶��� �ſ�? >>";
			dialogue.second = script;
			list.emplace_back(dialogue);
			script = L"<< ũ... ���õ� �ϳ� ���� ���ϴ�. >>";
			dialogue.second = script;
			list.emplace_back(dialogue);
			script = L"<< ����..? �̷��� ���� �����ϴ� ��, ������ �� �� ���̽� �� ����..? >>";
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
