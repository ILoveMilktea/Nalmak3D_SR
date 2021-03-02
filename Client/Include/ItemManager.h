#pragma once
#include "Component.h"

class ItemManager :
	public Component
{
public:
	struct Desc
	{

	};


	ItemManager(Desc* _Desc);
	virtual ~ItemManager();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;


private:
	static ItemManager*  m_instance;

public:
	static ItemManager* GetInstance();
	static void DeleteInstance();


public:
	class PlayerItem* FindItemObject(const wstring& _itemtype,
		const wstring& _typeValueName);

	bool BuyItem(const wstring& _itemName , const wstring& _typeValueName);
private:
	// <itemtype, vector<item>
	// 이름 : playeritem -> get info -> name
	unordered_map<wstring, vector<class PlayerItem*>> m_mapShopItem;

	
private:
	PlayerInfoManager* m_playerMgr;
};

