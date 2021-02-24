#pragma once
#include "Component.h"
class PlayerKitSelector :
	public Component
{
public:
	PlayerKitSelector();
	virtual ~PlayerKitSelector();




public:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

public:
	const unordered_map<wstring, vector<class UseKit*>>& GetPlayerSlot();

private:
	unordered_map<wstring, vector<class UseKit*>> m_playerSlot;


};

