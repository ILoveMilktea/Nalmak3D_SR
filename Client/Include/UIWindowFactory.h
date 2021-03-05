#pragma once
#ifndef __UIWINDOWNFACTORY_H__
#define __UIWINDOWNFACTORY_H__

#include "stdafx.h"
#include "Core.h"
#include "UIFactory.h"

#include "PlayerInfoManager.h"
#include "UIInteractor.h"
#include "Scripter.h"
#include "ItemManager.h"
#include "MenuAnimator.h"
#include "ItemButton.h"
#include "UIManager.h"

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

		float inoutAmount = 1000.f;
		float inoutSpeed = 0.5f;
		float secondAnimDelay = 1.2f;

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
				auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"START STAGE", CANVAS_GROUP_MAINWND_MAIN);

				menu->AddComponent<MenuAnimator>();
				menu->GetComponent<MenuAnimator>()->SetAnimator(inoutAmount, inoutSpeed, secondAnimDelay, Vector3(576.f, 230.f, 0.f));

			}

			// Menu 2 - WEAPON SHOP
			{
				EventHandler eventFunc = EventHandler([=]() {
					list<CanvasRenderer*> group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_MAIN);
					for (auto member : group)
					{
						member->GetComponent<MenuAnimator>()->AddStartDelay(-secondAnimDelay);
						member->GetComponent<MenuAnimator>()->OutAnim();
					}

					group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_PLAYERINFO);
					for (auto member : group)
					{
						member->GetComponent<MenuAnimator>()->AddStartDelay(-secondAnimDelay);
						member->GetComponent<MenuAnimator>()->OutAnim();
					}

					group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_SHOP);
					for (auto member : group)
					{
						member->GetComponent<MenuAnimator>()->AddStartDelay(secondAnimDelay);
						member->GetComponent<MenuAnimator>()->InAnim();
					}
				});
				auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"WEAPON SHOP", CANVAS_GROUP_MAINWND_MAIN);
				menu->AddComponent<MenuAnimator>();
				menu->GetComponent<MenuAnimator>()->SetAnimator(inoutAmount, inoutSpeed, secondAnimDelay + 0.1f, Vector3(576.f, 270.f, 0.f));

				// Shop
				{
					// Menu 0 - RETURN
					{
						EventHandler returnFunc = EventHandler([=]() {
							list<CanvasRenderer*> group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_SHOP);
							for (auto member : group)
							{
								member->GetComponent<MenuAnimator>()->AddStartDelay(-secondAnimDelay);
								member->GetComponent<MenuAnimator>()->OutAnim();
							}

							group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_MAIN);
							for (auto member : group)
							{
								member->GetComponent<MenuAnimator>()->AddStartDelay(secondAnimDelay);
								member->GetComponent<MenuAnimator>()->InAnim();
							}

							group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_PLAYERINFO);
							for (auto member : group)
							{
								member->GetComponent<MenuAnimator>()->AddStartDelay(secondAnimDelay);
								member->GetComponent<MenuAnimator>()->InAnim();
							}
						});
						auto menu = UIFactory::Prefab_MenuButton(returnFunc, L"RETURN", CANVAS_GROUP_MAINWND_SHOP);

						menu->AddComponent<MenuAnimator>(); 
						menu->GetComponent<MenuAnimator>()->SetMoveAmount(inoutAmount);
						menu->GetComponent<MenuAnimator>()->SetMoveDuration(inoutSpeed);

						menu->SetPosition(576.f - inoutAmount, 230.f);
					}



					int slotCount = 5;
					float delayInterval = 0.1f;
					float slotInterval = 40.f;
					wstring itemNames[5] = { L"AimMissile" , L"Cannon" , L"HomingMissile" , L"ClusterMissile" , L"Emp" };

					for (int i = 0; i < slotCount; ++i)
					{
						// Slot
						wstring curItemName = itemNames[i];
						EventHandler eventFunc = EventHandler([=]() {

							ItemManager::GetInstance()->BuyItem(L"Weapon", curItemName);

						});
						wstring txt = L"[ Weapon - " + itemNames[i] + L" ] ";
						auto menu = UIFactory::Prefab_MenuButton(eventFunc, txt, CANVAS_GROUP_MAINWND_SHOP);

						menu->AddComponent<MenuAnimator>();
						menu->GetComponent<MenuAnimator>()->SetAnimator(inoutAmount, inoutSpeed, delayInterval * i, Vector3(576.f - inoutAmount, 310.f + slotInterval * i, 0.f));
					}
				}
			}

			// Menu 3 - EQUIP WEAPON
			{

				EventHandler eventFunc = EventHandler([=]() {

					Core::GetInstance()->GetMainCamera()->GetComponent<StateControl>()->SetState(L"zoomIn");


					list<CanvasRenderer*> group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_MAIN);
					for (auto member : group)
					{
						member->GetComponent<MenuAnimator>()->AddStartDelay(-secondAnimDelay);
						member->GetComponent<MenuAnimator>()->OutAnim();
					}

					group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_PLAYERINFO);
					for (auto member : group)
					{
						member->GetComponent<MenuAnimator>()->AddStartDelay(-secondAnimDelay);
						member->GetComponent<MenuAnimator>()->OutAnim();
					}

					auto inven = PlayerInfoManager::GetInstance()->GetInven();
					auto item = inven.begin();
					size_t itemIndex = 0;

					group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_EQUIP);
					for (auto member : group)
					{
						//member->SetInteractive(true);
						member->SetBlockPicking(false);

						if (item != inven.end())
						{
							if (item->first == L"Weapon")
							{
								if (member->GetGameObject()->GetName() == L"ItemMenuButton")
								{
									// text
									member->GetComponent<ItemButton>()->SetText(item->second[itemIndex]);

									// button
									ItemButton* button = member->GetComponent<ItemButton>();
									PARTS_NUM num = button->GetPartsNumber();

									wstring type = item->first;
									wstring itemName = item->second[itemIndex];
									EventHandler eventFunc = EventHandler([=]() {
										PlayerInfoManager::GetInstance()->EquipItem(num, type, itemName);
									});
									button->ResetEvent(eventFunc);

									++itemIndex;
									if (itemIndex == item->second.size())
										++item;
								}
							}
							else
							{
								++item;
							}
						}
						else
						{
							if (member->GetGameObject()->GetName() == L"ItemMenuButton")
							{
								member->GetComponent<ItemButton>()->SetText(L"");
								//member->SetInteractive(false);
								member->SetBlockPicking(true);
							}
						}
						member->GetComponent<MenuAnimator>()->AddStartDelay(secondAnimDelay);
						member->GetComponent<MenuAnimator>()->InAnim();
					}
				});
				auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"EQUIP", CANVAS_GROUP_MAINWND_MAIN);

				menu->AddComponent<MenuAnimator>();
				menu->GetComponent<MenuAnimator>()->SetAnimator(inoutAmount, inoutSpeed, secondAnimDelay + 0.2f, Vector3(576.f, 310.f, 0.f));

				// EQUIP
				{
					// Menu 0 - RETURN
					{
						EventHandler returnFunc = EventHandler([=]() {
							Core::GetInstance()->GetMainCamera()->GetComponent<StateControl>()->SetState(L"autoRotate");

							list<CanvasRenderer*> group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_EQUIP);
							for (auto member : group)
							{
								member->GetComponent<MenuAnimator>()->AddStartDelay(-secondAnimDelay);
								member->GetComponent<MenuAnimator>()->OutAnim();
							}

							group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_PLAYERINFO);
							for (auto member : group)
							{
								member->GetComponent<MenuAnimator>()->AddStartDelay(secondAnimDelay);
								member->GetComponent<MenuAnimator>()->InAnim();
							}

							group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_MAIN);
							for (auto member : group)
							{
								member->GetComponent<MenuAnimator>()->AddStartDelay(secondAnimDelay);
								member->GetComponent<MenuAnimator>()->InAnim();
							}
						});
						auto menu = UIFactory::Prefab_MenuButton(returnFunc, L"RETURN", CANVAS_GROUP_MAINWND_EQUIP);

						menu->AddComponent<MenuAnimator>();
						menu->GetComponent<MenuAnimator>()->SetMoveAmount(inoutAmount);
						menu->GetComponent<MenuAnimator>()->SetMoveDuration(inoutSpeed);

						menu->SetPosition(576.f - inoutAmount, 230.f);
					}

					int slotCount = 6;
					float delayInterval = 0.1f;
					float slotInterval = 40.f;
					for (int i = 0; i < slotCount; ++i)
					{
						// Slot
						{
							EventHandler eventFunc = EventHandler([=]() {});
							auto menu = UIFactory::Prefab_ItemMenuButton(eventFunc, L"", CANVAS_GROUP_MAINWND_EQUIP);

							menu->AddComponent<MenuAnimator>();
							menu->GetComponent<MenuAnimator>()->SetAnimator(inoutAmount, inoutSpeed, delayInterval * i, Vector3(576.f - inoutAmount, 310.f + slotInterval * i, 0.f));

							menu->GetComponent<ItemButton>()->SetPartsNumber(FIRST_PARTS);
						}
					}
				}
			}
			// Menu 4 - STAGE SELECT (Button)
			{
				EventHandler eventFunc = EventHandler([=]() {
					Core::GetInstance()->LoadScene(L"stageSelect");
				});
				auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"RETURN TO MAP", CANVAS_GROUP_MAINWND_MAIN);
				//menu->GetComponent<CanvasRenderer>()->SetInteractive(true);

				menu->AddComponent<MenuAnimator>();
				menu->GetComponent<MenuAnimator>()->SetAnimator(inoutAmount, inoutSpeed, secondAnimDelay + 0.3f, Vector3(576.f, 350.f, 0.f));
			}

			// ==== Test Menu ========
			{

				//// Menu (2 - 0) - WEAPON (Button) !!!!!!!!!!!!!TEST!!!!!!!!!!!!!
				//{
				//	EventHandler eventFunc = EventHandler([=]() {

				//		ItemManager::GetInstance()->BuyItem(L"Weapon", L"AimMissile");

				//	});
				//	auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"(TEST)BUY WEAPON [ Weapon - AimMissile ] ", CANVAS_GROUP_MAINWND);
				//	menu->SetPosition(1600.f, 600.f);
				//}
				//{
				//	EventHandler eventFunc = EventHandler([=]() {

				//		PlayerInfoManager::GetInstance()->EquipItem(FIRST_PARTS, L"Weapon", L"AimMissile"); // 주무장으로 에임미사일을

				//	});
				//	auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"(TEST)EQUIP WEAPON [ Weapon - AimMissile ] ", CANVAS_GROUP_MAINWND);
				//	menu->SetPosition(1600.f, 650.f);
				//}
				////

				//// Menu (2 - 1) - WEAPON (Button) !!!!!!!!!!!!!TEST!!!!!!!!!!!!!
				//{
				//	EventHandler eventFunc = EventHandler([=]() {

				//		ItemManager::GetInstance()->BuyItem(L"Weapon", L"Cannon");

				//	});
				//	auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"(TEST)BUY WEAPON [ Weapon - Cannon ] ", CANVAS_GROUP_MAINWND);
				//	menu->SetPosition(1600.f, 700.f);
				//}
				//{
				//	EventHandler eventFunc = EventHandler([=]() {

				//		PlayerInfoManager::GetInstance()->EquipItem(SECOND_PARTS, L"Weapon", L"Cannon"); // 보조무장으로 캐논을

				//	});
				//	auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"(TEST)EQUIP WEAPON [ Weapon -Cannon ] ", CANVAS_GROUP_MAINWND);
				//	menu->SetPosition(1600.f, 750.f);
				//}
				////

				//// Menu (2 - 2) - EQuipSkill (Button) !!!!!!!!!!!!!TEST!!!!!!!!!!!!!
				//{
				//	EventHandler eventFunc = EventHandler([=]() {

				//		PlayerInfoManager::GetInstance()->EquipItem(FIRST_PARTS, L"Skill", L"EscapeMove"); //스킬슬롯 첫번째 파츠에 스킬을 셋하겠다.

				//	});
				//	auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"Test) SkillSlot - First Parts : EscapeMove", CANVAS_GROUP_MAINWND);
				//	menu->SetPosition(1600.f, 800.f);
				//}

				////For EmpMissile tes.t
				//{
				//	//EventHandler evetFunc = EventHandler([=]() {ItemManager::GetInstance()->BuyItem(L"Weapon", L"Emp"); });
				//	EventHandler eventFunc
				//		= EventHandler([=]() {PlayerInfoManager::GetInstance()->EquipItem(FIRST_PARTS, L"Weapon", L"Emp"); });
				//	auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"Test) Weapon - First Parts : Emp", CANVAS_GROUP_MAINWND);
				//	menu->SetPosition(1600.f, 850.f);

				//}
			}



		}
		// description (text)
		{
			auto script = UIFactory::Prefab_ItemExplane(L"Hi, please write down in this space what you want to explane about selected aircraft.", CANVAS_GROUP_MAINWND);
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
				auto info = PlayerInfoManager::GetInstance();

				SetFloatFunc setValueFunc =
					SetFloatFunc([=](float* _out, GetFloatFunc _func) {
					*_out = _func();
				});

				{
					int slotCount = 5;
					float delayInterval = 0.1f;
					float slotInterval = 30.f;
					wstring sliderNames[5] = { L"SPEED" , L"DURABILITY" , L"ATTACK" , L"DEFENCE" , L"======" };

					for (int i = 0; i < slotCount; ++i)
					{
						wstring curSliderName = sliderNames[i];

						auto name = UIFactory::Prefab_ItemContents_Name(curSliderName);
						//name->SetPosition(1555.f, 260.f + slotInterval * i);

						GetFloatFunc getValueFunc;
						
						switch (i)
						{
						case 0:
							getValueFunc = GetFloatFunc([=]() {return (float)PlayerInfoManager::GetInstance()->GetMaxSpeed(); });
							break;
						case 1:
							getValueFunc = GetFloatFunc([=]() {return (float)PlayerInfoManager::GetInstance()->GetMaxHp(); });
							break;
						case 2:
							getValueFunc = GetFloatFunc([=]() {return (float)PlayerInfoManager::GetInstance()->GetAttack(); });
							break;
						case 3:
							getValueFunc = GetFloatFunc([=]() {return (float)PlayerInfoManager::GetInstance()->GetAttack(); });
							break;
						case 4:
							getValueFunc = GetFloatFunc([=]() {return (float)PlayerInfoManager::GetInstance()->GetAttack(); });
							break;
						}

						auto bar = UIFactory::Prefab_ItemContents_Bar(CANVAS_GROUP_MAINWND_PLAYERINFO);
						EventHandler eventFunc =
							EventHandler([=]() {
							bar->GetComponent<Slider>()->UpdateFillAmount(setValueFunc, getValueFunc);
						});

						_player->GetComponent<UIInteractor>()->AddEventHandler(eventFunc);
						
						bar->AddComponent<MenuAnimator>();
						bar->GetComponent<MenuAnimator>()->SetAnimator(-inoutAmount, inoutSpeed, secondAnimDelay + delayInterval * i, Vector3(1740.f, 260.f + slotInterval * i, 0.f));

						name->SetParents(bar);
						name->SetPosition(-185.f, 260.f + slotInterval * i, 0.f);
					}
				}
			}
		}
	}

	static void StageWindow(GameObject* _player)
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
			auto numberTag = UIFactory::CreateImage(CANVAS_GROUP_STAGE1, L"numberTag");
			numberTag->SetScale(110.f, 60.f);
			numberTag->SetPosition(640.f, 540.f);
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

			// enemy detector
			{
				auto enemyDetector = UIFactory::Prefab_EnemyDetector(crosshair, CANVAS_GROUP_STAGE1);
				enemyDetector->SetPosition(WINCX*0.5f, WINCY*0.5f);
			}

		}

		// altitude
		{

			// altitude text
			auto text = UIFactory::Prefab_Stage_AltitudeText(L"ALT", CANVAS_GROUP_STAGE1);
			text->SetPosition(1270.f, 510.f);

			// box
			auto numberTag = UIFactory::CreateImage(CANVAS_GROUP_STAGE1, L"numberTag");
			numberTag->SetScale(110.f, 60.f);
			numberTag->SetPosition(1280.f, 540.f);
			numberTag->GetTransform()->RotateZ(180.f);
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


			// skill rolling center
			auto pivot = INSTANTIATE(OBJECT_TAG_UI, L"SkiilRollPivot");
			pivot->AddComponent<CanvasRenderer>();
			pivot->SetPosition(1920, 1080);
			UIManager::GetInstance()->SetSkillRotatePivot(pivot);
			// skill img 1
			{
				auto img = UIFactory::CreateImage(CANVAS_GROUP_STAGEWND, L"boundary");
				img->SetScale(100.f, 100.f);
				img->SetParents(pivot);
				img->SetPosition(-cosf(Deg2Rad * 30) * 240.f, -120.f);
				// 150, 130
			}
			// skill img 2
			{
				auto img = UIFactory::CreateImage(CANVAS_GROUP_STAGEWND, L"boundary");
				img->SetScale(100.f, 100.f);
				img->SetParents(pivot);
				img->SetPosition(cosf(Deg2Rad * 30) * 240.f, -120.f);
			}
			// skill img wait
			{
				auto img = UIFactory::CreateImage(CANVAS_GROUP_STAGEWND, L"boundary");
				img->SetScale(100.f, 100.f);
				img->SetParents(pivot);
				img->SetPosition(0.f, 240.f);
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
			wstring title = L"SPEAKER";
			wstring script = L"<< SCRIPT1 >>";

			Dialogue dialogue;
			dialogue.first = title;
			dialogue.second = script;

			list.emplace_back(dialogue);

			script = L"<< SCRIPT2 >>";
			dialogue.second = script;
			list.emplace_back(dialogue);
			script = L"<< SCRIPT3 >>";
			dialogue.second = script;
			list.emplace_back(dialogue);
			script = L"<< SCRIPT4 >>";
			dialogue.second = script;
			list.emplace_back(dialogue);
			script = L"<< SCRIPT5 >>";
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

	static void EvasionAirFireScript()
	{

	}

	static void BossUI()
	{
		//name
		auto name = UIFactory::Prefab_Stage_BossName(L"Jeon Johnson(24/Guro)");
		name->SetPosition(WINCX * 0.5f, -80.f);
		//hp slider
		auto slider = UIFactory::Prefab_Stage_BossHpSlider();
		slider->SetPosition(WINCX * 0.5f, -40.f);
	}
};



#endif // !__UIWINDOWNFACTORY_H__
