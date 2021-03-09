#pragma once
#include "PlayerItem.h"
class Player_ClusterMissile :
	public PlayerItem
{
public:
	Player_ClusterMissile(const ITEMINFO& copy);
	virtual ~Player_ClusterMissile();

	virtual void ItemShot() override;
	virtual void CreateBullet() override;
	virtual void DeleteBullet() override;

private:
	GameObject* m_bullet = nullptr;
	GameObject* m_parents = nullptr;

	class EnemyDetector* m_detector = nullptr;

};

