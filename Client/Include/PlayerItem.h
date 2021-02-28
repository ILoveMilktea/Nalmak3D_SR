#pragma once

class PlayerItem 
{
public:
	PlayerItem(const ITEMINFO& _info);
	virtual ~PlayerItem();

	
	//getter
public:
	const ITEMINFO& GetItmeInfo() { return m_itemInfo; }
protected:
	virtual void ItemShot() = 0;


protected:
	ITEMINFO m_itemInfo;
};

