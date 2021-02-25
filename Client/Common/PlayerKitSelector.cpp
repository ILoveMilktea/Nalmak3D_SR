#include "stdafx.h"
#include "PlayerKitSelector.h"
#include "UseKit.h"


PlayerKitSelector*::PlayerKitSelector::m_instance = nullptr;



PlayerKitSelector::PlayerKitSelector(Desc * _desc)
{

}

PlayerKitSelector::~PlayerKitSelector()
{
}

PlayerKitSelector * PlayerKitSelector::GetInstance()
{
	if (!m_instance)
	{
		auto instance = INSTANTIATE()->AddComponent<PlayerKitSelector>();
		m_instance = instance->GetComponent<PlayerKitSelector>();
		instance->SetDontDestroy(true);
	}
	return m_instance;
}

void PlayerKitSelector::DeleteInstance()
{
	

	if (m_instance)
		DESTROY(m_instance->GetGameObject());
	
}


void PlayerKitSelector::Initialize()
{
	UseKit::Desc kitInfo;
	kitInfo.wepontype = UseKit::CANNON_30MM;
	kitInfo.amorCount = 20;
	UseKit::Desc kitInfo2;
	kitInfo2.wepontype = UseKit::GUID_MISSILE;
	kitInfo2.amorCount = 10;


	m_garageSlot[L"Wepon"] = vector<UseKit::Desc*>{ &kitInfo , &kitInfo2 };

}

void PlayerKitSelector::Update()
{
}

void PlayerKitSelector::Release()
{
	for (auto& name : m_garageSlot)
	{
		name.second.clear();
	}
	m_garageSlot.clear();
	// 	for_each(.begin(), .end(), [](auto& rPair) 
	// 	{
	// 		if (rPair.second)
	// 		{
	// 			delete rPair.second; 
	// 			rPair.second = nullptr; 
	// 		}
	// 	});
}



