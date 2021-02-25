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
	//const unordered_map<wstring, vector<Component*>>& GetPlayerSlot();

	ItemDesc* FindSlotItme(const wstring& _name , ITEMTYPE _enumID);
	static void DeleteInstance();
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

private:
	unordered_map<wstring, vector<ItemDesc*>> m_garageSlot;

private:
	static PlayerKitSelector* m_instance;

};

