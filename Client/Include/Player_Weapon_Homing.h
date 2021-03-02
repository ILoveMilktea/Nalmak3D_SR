#pragma once
#ifndef __PLAYER_WEAPON_HOMING_H__
#define __PLAYER_WEAPON_HOMING_H__

#include "PlayerItem.h"
class EnemyDetector;
class Player_Weapon_Homing :
	public PlayerItem
{
public:
	enum MODE { SINGLE, MULTI };

public:
	Player_Weapon_Homing(const ITEMINFO& _copy);
	virtual ~Player_Weapon_Homing();

	virtual void ItemShot() override;
	virtual void CreateBullet() override;
	virtual void DeleteBullet() override;

private:
	list<GameObject*> m_bullet;
	float m_reloadTerm;
	float m_reloadTimer;

	GameObject* m_parents = nullptr;
	TimeManager* m_time = nullptr;
	EnemyDetector* m_detector = nullptr;
};


#endif // !__PLAYER_WEAPON_HOMING_H__
