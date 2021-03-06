#pragma once
#include "Component.h"
class ClusterBulletMove :
	public Component
{
public:
	struct Desc
	{
		float speed = 0.f;
		float accAngle = 10.f;
		int bulletCount = 10;
		GameObject* target = nullptr;
		Vector2 screenPos = {};
	};

public:
	ClusterBulletMove(Desc* _desc);
	virtual ~ClusterBulletMove();

	// ComponentÀ»(¸¦) ÅëÇØ »ó¼ÓµÊ
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
//	GameObject* FindEnemy(OBJECT_TAG _enum , float _mimDis = 0);

private:
	GameObject* m_player = nullptr;
	GameObject* m_target = nullptr;
	Vector2 m_screenPos = {};
	Vector3 m_firstDir = {};
private:
	float m_accAngle;
	float m_speed;
	int m_bulletCount;

private:
	bool m_start = false;
};
