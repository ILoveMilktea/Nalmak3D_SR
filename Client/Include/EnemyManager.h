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
	int					Get_EnemyCount() const;
	list<GameObject*>	Get_EnemyList() const;
	int					Get_BossHp() const;
	const Vector3&		Get_BossPos() const;
	int					Get_BossCount() const;
	GameObject*			Get_Boss();

public: /* Settttt */
	void		Add_EnemyCount(int _count);
	GameObject* NearFindEenemy( GameObject* _finderObj, float _minDis =0 );
	void		Boss_Release();

public: /* Funcs */
	void		Destroy_AllEnemy();

	void		Enemy_Spawn_Debug(Vector3 _scale = Vector3(0.2f, 0.2f, 0.2f),
		ENEMY_STATE _initState = ENEMY_STATE::DEBUGGING,
		ENEMY_STATUS _status = ENEMY_STATUS());

	void		Enemy_Spawn(Vector3 _pos = Vector3(0.f,0.f,0.f),
		Vector3 _scale = Vector3(0.2f, 0.2f, 0.2f),
		//Quaternion _rot = Quaternion(0.f,0.f,0.f,0.f),
		ENEMY_STATE _initState =ENEMY_STATE::IDLE,
		ENEMY_STATUS _status = ENEMY_STATUS(),
		BULLET_STATUS _gun = BULLET_STATUS(),
		BULLET_STATUS _missile = BULLET_STATUS(),
		BULLET_STATUS _homing = BULLET_STATUS());

	void Enemy_Spawn_Test(ENEMY_STATE _initState, Vector3 pos = Vector3(0.f,0.f,0.f));

	void Enemy_Spawn_Normal();
	void Enemy_Spawn_Huge();
	void Enemy_Spawn_Quick();


	void Enemy_Spawn_Evasion(
		ENEMY_EVASION_STATE _initState = ENEMY_EVASION_STATE::SLIDE,
		Vector3 _spawnPos = Vector3(0.f, 500.f, 0.f),
		Vector3 _destpos = Vector3(0.f, 0.f, 0.f),
		float _lifeTime = 5.f);

	void MidBoss_Spawn(Vector3 _pos);
	GameObject* Boss_Spawn();

	void		Player_FovSpawnTest(bool _front, float _distance);
	Vector3		Pos_ScreenToWorld(float _x, float _y, float _distance);


public: /* Stage1 - tutorial + dogFight*/
	void Spawn_S1P1_Normal();
	void Spawn_S1P1_Huge();
	void Spawn_S1P1_Quick();


private:
	GameObject*		m_pBoss = nullptr;
	int				m_iEnemyCount = 0;
	int				m_iBossCount = 0;

	StateControl* m_pStateControl;
};
