#pragma once
#include "PlayerItem.h"
class AimMissile :
	public PlayerItem
{
public:
	AimMissile(const ITEMINFO& copy);
	virtual ~AimMissile();

	// PlayerItem을(를) 통해 상속됨
	virtual void ItemShot() override;
};

