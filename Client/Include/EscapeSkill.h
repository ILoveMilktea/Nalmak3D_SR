#pragma once
#include "PlayerItem.h"
class EscapeSkill :
	public PlayerItem
{
public:
	EscapeSkill(const ITEMINFO& copy);
	virtual ~EscapeSkill();

	// PlayerItem을(를) 통해 상속됨
	virtual void ItemShot() override;
	virtual void CreateBullet() override;
	virtual void DeleteBullet() override;

	// PlayerItem을(를) 통해 상속됨
};

