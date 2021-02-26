#pragma once
#include "UseItem.h"
class AimMissile :
	public UseItem
{
public:
	enum SIDE_TYPE { LEFT_SIDE, RIGHT_SIDE , SIDE_MAX };
	struct Desc
	{
		ItemDesc useItem;
	};
public:
	AimMissile(Desc* _desc);


	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Shooting(bool _check) override;

	void SetWeapon();

private:
	GameObject * missile[SIDE_MAX];
	Vector3 m_playerDir = {};
	Quaternion m_playerRot = {};
	bool ShotCheck = false;
	

private:
	Core* m_core;
};

