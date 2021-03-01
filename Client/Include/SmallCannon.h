#pragma once
#include "PlayerItem.h"
class SmallCannon :
	public PlayerItem
{
public:
	SmallCannon(const ITEMINFO& copy);
	virtual ~SmallCannon();



	// PlayerItem��(��) ���� ��ӵ�
	virtual void ItemShot() override;
	virtual void CreateBullet() override;
	virtual void DeleteBullet() override;


private:
	GameObject* m_bullet;

private:
	GameObject* m_parents = nullptr;

};

