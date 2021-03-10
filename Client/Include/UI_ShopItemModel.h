#pragma once
#include "Component.h"
class UI_ShopItemModel :
	public Component
{
public:
	struct Desc
	{
		GameObject* cam;
	};
public:
	UI_ShopItemModel(Desc* _desc);
	~UI_ShopItemModel();

	virtual void Initialize() override;
	virtual void Update() override;

private:
	GameObject* m_mainCam;
};

