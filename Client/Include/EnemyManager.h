#pragma once

#include "Component.h"

class EnemyManager : public Component
{
public:
	struct Desc
	{
	
	};


public:
	EnemyManager(Desc* _Desc);
	virtual ~EnemyManager();

private:
	static EnemyManager* m_Instance;
public:
	static EnemyManager* GetInstance();
	static void DeleteInstance();

public:
	virtual void Initialize() override;
	virtual void Update() override;

public: /* Gettttt */
	int Get_EnemyCount() const;
	list<GameObject*> Get_EnemyList() const;

public: /* Settttt */
	void Add_EnemyCount(int _count);


public: /* Funcs */
	void Destroy_AllEnemy();
	void Enemy_Spawn(Vector3 _pos = Vector3(0.f,0.f,0.f), 
		ENEMY_STATE _initState =ENEMY_STATE::IDLE,
		ENEMY_STATUS _status = ENEMY_STATUS(),
		BULLET_STATUS _gun = BULLET_STATUS(), 
		BULLET_STATUS _missile = BULLET_STATUS(), 
		BULLET_STATUS _homing = BULLET_STATUS());

	void Boss_Spawn();

private:
	StateControl* m_pStateControl = nullptr;
	int				m_iEnemyCount = 0;
};
