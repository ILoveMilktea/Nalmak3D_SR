#pragma once
#include "UseItem.h"
class AimMissile :
	public UseItem
{
	// 
public:
	AimMissile(ItemDesc* _desc);


	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Shooting() override;
};

