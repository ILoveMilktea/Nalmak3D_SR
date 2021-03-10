#include "stdafx.h"
#include "UI_ShopItemModel.h"


UI_ShopItemModel::UI_ShopItemModel(Desc * _desc)
{
	m_mainCam = _desc->cam;
}

UI_ShopItemModel::~UI_ShopItemModel()
{
}

void UI_ShopItemModel::Initialize()
{
}

void UI_ShopItemModel::Update()
{
	m_transform->RotateX(dTime * 20.f);
	m_transform->RotateY(dTime * 30.f);

	Transform* camTr = m_mainCam->GetTransform();

	m_transform->position = camTr->GetWorldPosition() + camTr->GetForward() * 3;
}
