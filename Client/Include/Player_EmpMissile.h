#pragma once
#include "PlayerItem.h"
class Player_EmpMissile :
	public PlayerItem
{
public:
	Player_EmpMissile(const ITEMINFO& _info);
	virtual ~Player_EmpMissile();

	virtual void ItemShot() override;
	virtual void CreateBullet() override;
	virtual void DeleteBullet() override;

private:
	GameObject* Emp = nullptr;

		  

	// PlayerItem을(를) 통해 상속됨

};

