#pragma once
#include "PlayerItem.h"
class Player_EmpMissile :
	public PlayerItem
{
public:
	Player_EmpMissile(const ITEMINFO& _info);
	virtual ~Player_EmpMissile();

	// PlayerItem��(��) ���� ��ӵ�
	virtual void ItemShot() override;
	virtual void CreateBullet() override;
	virtual void DeleteBullet() override;

public:

public:

private:
	GameObject* Emp = nullptr;

		  
};

