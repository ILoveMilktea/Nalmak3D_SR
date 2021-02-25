#pragma once
#include "Component.h"

class PlayerKitSelector :
	public Component
{
public:
	struct Desc
	{

	};

public:
	PlayerKitSelector(Desc* _desc);
	virtual ~PlayerKitSelector();

public:
	static PlayerKitSelector* GetInstance();
	

	ItemDesc* FindSlotItme(const wstring& _name , ITEMTYPE _enumID);
	static void DeleteInstance();
public:
	virtual void Initialize() override;
	virtual void Update() override;

private:
	unordered_map<wstring, vector<ItemDesc*>> m_garageSlot;

private:
	static PlayerKitSelector* m_instance;

};

