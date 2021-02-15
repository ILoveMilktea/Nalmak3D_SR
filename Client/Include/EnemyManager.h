#pragma once

/*
몬스타 매니져
	몬스타 보관
	몬스타 생성
	현재 전투 스테이트 받아오기
*/
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

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
	//void Get_CurHp();
	//void Get_Transform();
	const int& Get_EnemyCount() const;

public: /* Settttt */


public: /* Funcs */
	void Enemy_Spawn(Vector3 _pos);


private:
	//list<GameObject*> list_Enemies;

};

#endif