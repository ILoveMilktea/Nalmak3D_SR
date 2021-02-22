#pragma once

<<<<<<< HEAD
=======

#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

>>>>>>> 0579131a4def43ac46d68430816dfd5ba2725b8f
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
	//const int& Get_EnemyCount() const;

public: /* Settttt */


public: /* Funcs */
	void Enemy_Spawn(Vector3 _pos);
	void Spawn_Rush();
	void Spawn_Chase();

private:


};
