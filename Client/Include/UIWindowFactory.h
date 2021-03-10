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
#include "StageManager.h"
#include "GameManager.h"

#include "UIManager.h"

#include "UI_ShopMenu_Animator.h"
#include "UI_ShopWnd_Animator.h"
#include "UI_ShopItemModel.h"
#include "PlayerShooter.h"

#include "UIFactory.h"

// menu animator -> left move

// UI_ShopMenu_Animator ->
class UIWindowFactory
{
public:

	static void GarageMainWindow(GameObject* _player)
	{
		auto interactiveController = INSTANTIATE();

		//// reference
		//{
		//	SingleImage::Desc desc_si;
		//	desc_si.textureName = L"garage_background";
		//	auto background = INSTANTIATE();
		//	background->AddComponent<CanvasRenderer>();
		//	background->AddComponent<SingleImage>(&desc_si);
		//	background->GetComponent<CanvasRenderer>()->SetFade(0.11f);
		//	background->SetPosition(WINCX * 0.5f, WINCY * 0.5f);
		//	background->SetScale(WINCX, WINCY);
		//}

		float inoutAmount = 3000.f;
		float inoutSpeed = 0.8f;
		float secondAnimDelay = 1.2f;

		// Menu
		{
			// Title (text)
			{
				auto title = UIFactory::Prefab_MenuTitle(L"MAIN MENU", CANVAS_GROUP_MAINWND);
				title->SetPosition(576.f, 120.f);

				auto bg = UIFactory::Prefab_MenuBackground(CANVAS_GROUP_MAINWND);
				bg->SetPosition(HALF_WINCX - 600, 110);
			}

			// Menu 1 - START STAGE	(Button)
			{
				EventHandler eventFunc;

				wstring temp = GameManager::GetInstance()->Get_NextStage();
				eventFunc = EventHandler([=]() {Core::GetInstance()->LoadScene(temp);});


				auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"START STAGE", CANVAS_GROUP_MAINWND_MAIN);

				menu->AddComponent<MenuAnimator>();
				menu->GetComponent<MenuAnimator>()->SetAnimator(inoutAmount, inoutSpeed, secondAnimDelay, Vector3(576.f, 230.f, 0.f));

			}

			// Menu 2 - WEAPON SHOP
			{
				EventHandler eventFunc = EventHandler([=]() {
					list<CanvasRenderer*> group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_MAIN); // main menu 4 + return
					for (auto member : group)
					{
						member->GetComponent<MenuAnimator>()->AddStartDelay(-secondAnimDelay);
						member->GetComponent<MenuAnimator>()->OutAnim();
					}
					group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_PLAYERINFO); // slider
					for (auto member : group)
					{
						member->GetComponent<MenuAnimator>()->AddStartDelay(-secondAnimDelay);
						member->GetComponent<MenuAnimator>()->OutAnim();
					}

					group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_SHOP); // return
					for (auto member : group)
					{
						member->GetComponent<MenuAnimator>()->AddStartDelay(secondAnimDelay);
						member->GetComponent<MenuAnimator>()->InAnim();
					}

					group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_SHOPWND); // shop panel
					for (auto member : group)
					{
						member->GetComponent<UI_ShopWnd_Animator>()->AddStartDelay(secondAnimDelay);
						member->GetComponent<UI_ShopWnd_Animator>()->OnAnim();
					}

					group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_SHOPMENU); // weapon icon
					for (auto member : group)
					{
						member->GetComponent<CanvasRenderer>()->SetActive(true);
						member->GetComponent<UI_ShopMenu_Animator>()->AddStartDelay(secondAnimDelay - 0.05f);
						member->GetComponent<UI_ShopMenu_Animator>()->OnAnim();
					}

					group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_SHOP_BUYMENU); // no animation -> enum shop no animation
					for (auto member : group)
					{
						member->GetComponent<CanvasRenderer>()->SetActive(true);
					}
				});
				auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"WEAPON SHOP", CANVAS_GROUP_MAINWND_MAIN);
				menu->AddComponent<MenuAnimator>();
				menu->GetComponent<MenuAnimator>()->SetAnimator(inoutAmount, inoutSpeed, secondAnimDelay + 0.1f, Vector3(576.f, 270.f, 0.f)); // left move

				Garage_ShopWindow();
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
						member->GetComponent<MenuAnimator>()->InAnim();
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
										PlayerInfoManager::GetInstance()->SetWeaponSpawnPos(num);
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
								member->GetComponent<MenuAnimator>()->OutAnim();
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
					int partNum = 0;
					for (int i = 0; i < slotCount; ++i)
					{
						// Slot
						{
							EventHandler eventFunc = EventHandler([=]() {});
							auto menu = UIFactory::Prefab_ItemMenuButton(eventFunc, L"", CANVAS_GROUP_MAINWND_EQUIP);

							menu->AddComponent<MenuAnimator>();
							menu->GetComponent<MenuAnimator>()->SetAnimator(inoutAmount, inoutSpeed, delayInterval * i, Vector3(576.f - inoutAmount, 310.f + slotInterval * i, 0.f));

							menu->GetComponent<ItemButton>()->SetPartsNumber(PARTS_NUM(i));
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


				// description (text)
				{
					auto script = UIFactory::Prefab_ItemExplane(L"Hi, please write down in this space what you want to explane about selected aircraft.", CANVAS_GROUP_MAINWND);
					script->SetPosition(576.f, 880.f);

					script->SetParents(menu);
					script->SetPosition(script->GetTransform()->position - menu->GetTransform()->position);
				}
			}



		}


		// player info
		{
			// ItemTitle

			auto title = UIFactory::Prefab_ItemTitle(L"F - 15");
			title->SetPosition(1640.f, 195.f);
			// ItemSubtitle
			auto subtitle = UIFactory::Prefab_ItemSubtitle(L"[Description about item]");
			subtitle->SetPosition(1640.f, 230.f);
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
						bar->GetComponent<MenuAnimator>()->SetAnimator(inoutAmount, inoutSpeed, secondAnimDelay + delayInterval * i, Vector3(1740.f, 260.f + slotInterval * i, 0.f));

						name->SetParents(bar);
						name->SetPosition(-185.f, 0.f, 0.f);

						if (i == 0)
						{
							title->SetParents(bar);
							title->SetPosition(title->GetTransform()->position - bar->GetTransform()->position);
							subtitle->SetParents(bar);
							subtitle->SetPosition(subtitle->GetTransform()->position - bar->GetTransform()->position);
						}
					}
				}
			}
		}
	}

	static void Garage_ShopWindow()
	{
		float inoutAmount = 1000.f;
		float inoutSpeed = 0.5f;
		float secondAnimDelay = 1.2f;

		// Menu 0 - RETURN
		{
			EventHandler returnFunc = EventHandler([=]() {
				list<CanvasRenderer*> group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_SHOP);
				for (auto member : group)
				{
					member->GetComponent<MenuAnimator>()->AddStartDelay(-secondAnimDelay);
					member->GetComponent<MenuAnimator>()->OutAnim();
				}

				group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_SHOPWND);
				for (auto member : group)
				{
					member->GetComponent<UI_ShopWnd_Animator>()->AddStartDelay(-secondAnimDelay);
					member->GetComponent<UI_ShopWnd_Animator>()->OffAnim();
				}

				group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_SHOPMENU);
				for (auto member : group)
				{
					//member->GetComponent<UI_ShopMenu_Animator>()->AddStartDelay(-secondAnimDelay);
					//member->GetComponent<UI_ShopMenu_Animator>()->OffAnim();
					member->GetComponent<CanvasRenderer>()->SetActive(false);
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

				group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_SHOP_BUYMENU);
				for (auto member : group)
				{
					member->GetComponent<CanvasRenderer>()->SetActive(false);
				}

				auto model = UIManager::GetInstance()->GetShopItemModel();
				model->SetActive(false);
			});
			auto menu = UIFactory::Prefab_MenuButton(returnFunc, L"RETURN", CANVAS_GROUP_MAINWND_SHOP);

			menu->AddComponent<MenuAnimator>();
			menu->GetComponent<MenuAnimator>()->SetAnimator(inoutAmount, inoutSpeed, 0.f, Vector3(576.f - inoutAmount, 230.f, 0.f));

		}

		// right menu
		{
			// shop wnd
			{
				// background image
				{
				float animAmount = -400.f;
				float animSpeed = 0.5f;
				float secondAnimDelay = 0.5f;

				//190, 227, 253, 255

				auto background = UIFactory::CreateImage(CANVAS_GROUP_MAINWND_SHOPWND, L"ui_shopwnd_bg");
				background->SetScale(360.f, 550.f);
				background->GetComponent<CanvasRenderer>()->SetColor(Vector4(0.74f, 0.89f, 1.f, 1.f));

				auto gradation = UIFactory::CreateImage(CANVAS_GROUP_MAINWND_SHOP_NOANIM, L"ui_shopwnd_gradation");
				gradation->SetParents(background);
				gradation->SetScale(350.f, 540.f);
				gradation->GetComponent<CanvasRenderer>()->SetColor(Vector4(0.74f, 0.89f, 1.f, 1.f));


				background->AddComponent<UI_ShopWnd_Animator>();
				background->GetComponent<UI_ShopWnd_Animator>()->
					SetAnimator(animAmount, animAmount * 0.1f, animSpeed, 0.f
						, Vector3(WINCX + background->GetTransform()->scale.x * 0.5f, WINCY * 0.5f - 100.f, 0.f));
				}

				// line effect image
			}



			// Model

			MeshRenderer::Desc desc_Mesh;
			desc_Mesh.meshName = L"kfir_weapon1";

			UI_ShopItemModel::Desc desc_model;
			desc_model.cam = Core::GetInstance()->GetMainCamera()->GetGameObject();
			auto weaponModel = INSTANTIATE();
			weaponModel->AddComponent<MeshRenderer>(&desc_Mesh);
			weaponModel->AddComponent<UI_ShopItemModel>(&desc_model);
			weaponModel->SetPosition(0.f, 0.f, 0.f);
			weaponModel->SetActive(false);

			UIManager::GetInstance()->SetShopItemModel(weaponModel);

			// Weapon buttons
			{
				int slotCount = 4;
				float delayInterval = 0.05f;
				float slotInterval = 80.f;


				//L"kfir_weapon1", //L"su34_weapon1" //L"su34_weapon2" // L"su34_weapon3 //L"su34_weapon3"
				wstring itemNames[5] = { L"AimMissile" ,  L"HomingMissile" , L"ClusterMissile" , L"Emp" };
				wstring itmeMtrl[5] = { L"kfir" , L"su34" , L"su34" , L"su34" , L"su34" };

				for (int i = 0; i < slotCount; ++i)
				{
					// Slot
					wstring curItemName = itemNames[i];
					wstring mtrlName = itmeMtrl[i];
					EventHandler onEvent = EventHandler([=]() {
						// Load Item
						// 0. unselect other toggle
						list<CanvasRenderer*> group = CanvasGroup::GetInstance()->GetGroup(CANVAS_GROUP_MAINWND_SHOPMENU);
						for (auto member : group)
						{
							member->GetComponent<Toggle>()->UnselectToggle();
						}
						// 1. load model
						wstring modelName = ItemManager::GetInstance()->LoadItemModel(L"Weapon", curItemName);

						auto model = UIManager::GetInstance()->GetShopItemModel();
						model->GetComponent<MeshRenderer>()->SetMesh(modelName);
						model->GetComponent<MeshRenderer>()->SetMaterial(mtrlName);
						model->SetActive(true);
						// 2. load status at slider
						UIManager::GetInstance()->SetCurrentSelectItem(curItemName);
						// 3. load price


					});
					EventHandler offEvent = EventHandler([=]() {
						// remove Item
						weaponModel->SetActive(false);
						auto player = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);
						player->GetTransform()->position = { 0,0,0 };
						player->GetTransform()->SetRotation(0, 0, 0);

					});
					wstring img = L"s" + to_wstring(i + 1);
					auto menu = UIFactory::Prefab_ShopMenuToggle(onEvent, offEvent, img, CANVAS_GROUP_MAINWND_SHOPMENU);

					menu->AddComponent<UI_ShopMenu_Animator>();
					menu->GetComponent<UI_ShopMenu_Animator>()->SetAnimator(0.f, 0.5f, delayInterval * i, Vector3(1680.f, 270.f + slotInterval * i, 0.f));
					menu->GetComponent<CanvasRenderer>()->SetActive(false);
				}

				// left price img
				// price number

				// buy button
				{
					EventHandler openPopupFunc = EventHandler([=]() {
						UIManager::GetInstance()->BuyPopupOn();
					});
					auto buyButton = UIFactory::Prefab_ItemBuy_Button(openPopupFunc, L"BUY ITEM", CANVAS_GROUP_MAINWND_SHOP_BUYMENU);

					buyButton->SetPosition(Vector3(1680.f, 700.f, 0.f));
				}
			}

			// Weapon Status Slider
			{
				// single dpm text
				auto singleDpm_text = UIFactory::Prefab_ItemStat_Text(L"SINGLE DPM", CANVAS_GROUP_MAINWND_SHOP_BUYMENU);
				// single dpm slider
				auto singleDpm_slider = UIFactory::Prefab_ItemStat_Slider(CANVAS_GROUP_MAINWND_SHOP_BUYMENU);
				singleDpm_text->SetParents(singleDpm_slider);
				singleDpm_text->SetPosition(-140.f, 0.f);
				singleDpm_slider->SetPosition(400.f, 800.f);

				// multi dpm text
				auto multiDpm_text = UIFactory::Prefab_ItemStat_Text(L"MULTI DPM", CANVAS_GROUP_MAINWND_SHOP_BUYMENU);
				// multi targe dpm slider
				auto multiDpm_slider = UIFactory::Prefab_ItemStat_Slider(CANVAS_GROUP_MAINWND_SHOP_BUYMENU);
				multiDpm_text->SetParents(multiDpm_slider);
				multiDpm_text->SetPosition(-140.f, 0.f);
				multiDpm_slider->SetPosition(400.f, 830.f);
			}


			// Popup
			{
				auto popup = INSTANTIATE(OBJECT_TAG_UI,L"UI_BuyPopup");
				UIManager::GetInstance()->SetBuyPopup(popup);
				popup->AddComponent<CanvasRenderer>();
				popup->SetPosition(WINCX* 0.5f, WINCY * 0.5f);

				// background

				auto background = UIFactory::CreateImage(CANVAS_GROUP_MAINWND_SHOP_BUYPOPUP, L"ui_popup");
				background->SetParents(popup);
				background->SetPosition(0.f,0.f,0.f);
				background->SetScale(WINCX* 0.5f, WINCY * 0.5f);
				background->GetComponent<CanvasRenderer>()->SetColor(Vector4(0.3f, 0.3f,0.5f, 0.5f));


				// notice text
				auto notice = UIFactory::Prefab_Popup_Text(L"구?매", CANVAS_GROUP_MAINWND_SHOP_BUYPOPUP);
				notice->SetParents(popup);
				background->SetPosition(0.f, 0.f, 0.f);
				notice->SetScale(WINCX* 0.5f, WINCY * 0.5f);


				// ok button
				{
					EventHandler buyFunc = EventHandler([=]() {
						// popup off
						UIManager::GetInstance()->BuyItem();
						UIManager::GetInstance()->BuyPopupOff();
					});
					auto okButton = UIFactory::Prefab_Popup_OKButton(buyFunc, CANVAS_GROUP_MAINWND_SHOP_BUYPOPUP);
					okButton->SetParents(popup);
					okButton->SetPosition(-background->GetTransform()->scale.x * 0.25f, background->GetTransform()->scale.y * 0.25f, 0.f);
				}
				// cancel button
				{
					EventHandler cancelFunc = EventHandler([=]() {
						// popup off
						UIManager::GetInstance()->BuyPopupOff();
					});
					auto cancelButton = UIFactory::Prefab_Popup_CancelButton(cancelFunc, CANVAS_GROUP_MAINWND_SHOP_BUYPOPUP);
					cancelButton->SetParents(popup); 
					cancelButton->SetPosition(background->GetTransform()->scale.x * 0.25f, background->GetTransform()->scale.y * 0.25f, 0.f);
				}


				// must be last operation
				popup->SetActive(false);
			}
		}


		// bottom menu
		{
		/*
			

		*/
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
					return 5.f;
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

			script = L"MooGi Test gogo!\nJotBoBs 4Mari Cut";
			dialogue.second = script;
			list.emplace_back(dialogue);
			script = L"The Big one cant damaged Machinegun, use Missile!";
			dialogue.second = script;
			list.emplace_back(dialogue);
			script = L"Faster is Die faster. show what u got";
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

	static void ResultSceneTest()
	{
		// ==== Result Scene Test ====
		{
			EventHandler eventFunc = EventHandler([=]() {Core::GetInstance()->LoadScene(L"stageSelect"); });
			auto menu = UIFactory::Prefab_MenuButton(eventFunc, L"OK ~ReturnToStageSelectScene~", CANVAS_GROUP_RESULT);

			menu->AddComponent<MenuAnimator>();
			menu->GetComponent<MenuAnimator>()->SetMoveAmount(1200.f);
			menu->GetComponent<MenuAnimator>()->SetMoveDuration(1.f);
			menu->GetComponent<MenuAnimator>()->AddStartDelay(1.5f);
			menu->SetPosition(960.f, 540.f);
		}
	}

};



#endif // !__UIWINDOWNFACTORY_H__
