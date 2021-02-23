#include "stdafx.h"
#include "PrintInfo.h"



PrintInfo::PrintInfo(Desc * _desc)
{
}

PrintInfo::~PrintInfo()
{
}

void PrintInfo::Initialize()
{
}

void PrintInfo::Update()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F1))
		CanvasGroup::GetInstance()->SetObjectActive(CANVAS_GROUP_NONE, true);
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_F2))
		CanvasGroup::GetInstance()->SetObjectActive(CANVAS_GROUP_NONE, false);
}
