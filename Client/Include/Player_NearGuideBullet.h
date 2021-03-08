#pragma once
#include "Component.h"
class Player_NearGuideBullet :
	public Component
{
public:
	struct Desc
	{
		Vector3 firstTarget;
		float speed;
	};


public:
	Player_NearGuideBullet(Desc * _desc);
	virtual ~Player_NearGuideBullet();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release()override;


	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;

private:
	//GameObject * FindEnemy(OBJECT_TAG _enum, float _mimDis = 0);
private:
	Vector3 m_firstTarget;
	bool	m_bFinish;
private:
	GameObject* m_player;
	GameObject* m_target;
	class EnemyDetector* m_enemyDetector;
	Vector3 m_firstDir;
	StateControl * m_stateControl;
	float m_speed;
	int m_dmg;
};

