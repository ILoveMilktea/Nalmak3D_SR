#include "stdafx.h"
#include "PlayerKitSelector.h"


PlayerKitSelector::PlayerKitSelector()
{
}


PlayerKitSelector::~PlayerKitSelector()
{
}

const unordered_map<wstring, vector<class UseKit*>>& PlayerKitSelector::GetPlayerSlot()
{
	return m_playerSlot;
}

void PlayerKitSelector::Initialize()
{
}

void PlayerKitSelector::Update()
{
}


