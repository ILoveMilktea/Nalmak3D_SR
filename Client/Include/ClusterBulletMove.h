#pragma once
#include "Component.h"
class ClusterBulletMove :
	public Component
{
public:
	struct Desc
	{
		float speed = 0.f;
	};

public:
	ClusterBulletMove(Desc* _desc);
	virtual ~ClusterBulletMove();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

	virtual void OnTriggerEnter(Collisions& _collision)override;
public:
	GameObject* FindEnemy(OBJECT_TAG _enum , float _mimDis = 0);

private:
	GameObject* m_player = nullptr;
	
	Vector3 m_firstDir = {};
	float m_speed;
	float m_bFirstShot;

};

