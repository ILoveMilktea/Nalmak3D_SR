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

	// Component��(��) ���� ���ӵ�
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
	Vector3 m_firstDir;
	Vector3 m_finalTargetPos;
	bool	m_bFinish;
private:
	GameObject* m_player;
	GameObject* m_target;
	GameObject* m_finder = nullptr;
	class EnemyDetector* m_enemyDetector;

	StateControl * m_stateControl;
	float m_speed;
	int m_dmg;
};
