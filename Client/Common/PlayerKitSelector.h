#pragma once
#include "Component.h"
#include "UseKit.h"

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
	static void DeleteInstance();
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

private:
	unordered_map<wstring, vector<UseKit::Desc*>> m_garageSlot;

private:
	static PlayerKitSelector* m_instance;

};

