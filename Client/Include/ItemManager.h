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

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	void CreateItem(); // �����ϴ� �� �Լ��� ���� - �ؿ�

private:
	static ItemManager*  m_instance;

public:
	static ItemManager* GetInstance();
	static void DeleteInstance();


public:
	class PlayerItem* FindItemObject(const wstring& _itemtype,
		const wstring& _typeValueName);

	bool BuyItem(const wstring& _itemName , const wstring& _typeValueName);
	wstring LoadItemModel(const wstring & _itemtype, const wstring& _itemName);

private:
	// <itemtype, vector<item>
	// �̸� : playeritem -> get info -> name
	unordered_map<wstring, vector<class PlayerItem*>> m_mapShopItem;

	

private:
	PlayerInfoManager* m_playerMgr;
};

