#pragma once
#include "PlayerItem.h"
class AimMissile :
	public PlayerItem
{
public:
	AimMissile(const ITEMINFO& copy);
	virtual ~AimMissile();

	// PlayerItem��(��) ���� ��ӵ�
	virtual void ItemShot() override;
};

