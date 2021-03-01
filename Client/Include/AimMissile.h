#pragma once
#include "PlayerItem.h"
class AimMissile :
	public PlayerItem
{
public:
	AimMissile(const ITEMINFO& copy);
	virtual ~AimMissile();

	virtual void ItemShot() override;
	virtual void CreateBullet() override;
	virtual void DeleteBullet() override;

private:
	
	GameObject* m_bullet[2];
	// PlayerItem��(��) ���� ��ӵ�

private:
	GameObject* m_parents = nullptr;
};

