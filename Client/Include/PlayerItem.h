#pragma once

class PlayerItem 
{
public:
	PlayerItem(const ITEMINFO& _info);
	virtual ~PlayerItem();

	
	//getter
public:
	const ITEMINFO& GetItmeInfo() { return m_itemInfo; }
	const bool& GetShotCheck() { return m_shotCheck; }
	const wstring& GetModelName() { return m_itemInfo.modelName; }
	
	//setter
public:
	void SetShotCheck(bool _check) { m_shotCheck = _check; }
	void SetCreatePos(Vector3 _pos) { m_itemInfo.createPos = _pos;  }

	virtual void ItemShot() = 0;
	virtual void CreateBullet() = 0;
	virtual void DeleteBullet() = 0;

	
protected:
	ITEMINFO m_itemInfo;
	bool m_shotCheck = false;
};

