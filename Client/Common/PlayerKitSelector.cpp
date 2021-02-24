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
	//m_playerSlot.emplace(L"Wepon", &kitInfo);

	//vector<class UseKit::Desc*>().push_back

//	m_garageSlot[L"Wepon"] = vector<UseKit::Desc*>{ &kitInfo };

}

void PlayerKitSelector::Update()
{
}

void PlayerKitSelector::Release()
{
	/*for (auto& name : m_playerSlot)
	{
		for (auto & value : name.second)
		{
			if (value)
			{
			
			}
		}

	}*/

	// 	for_each(.begin(), .end(), [](auto& rPair) 
	// 	{
	// 		if (rPair.second)
	// 		{
	// 			delete rPair.second; 
	// 			rPair.second = nullptr; 
	// 		}
	// 	});
}



