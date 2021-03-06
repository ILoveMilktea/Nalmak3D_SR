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



private:
	//GameObject * FindEnemy(OBJECT_TAG _enum, float _mimDis = 0);
private:
	Vector3 m_firstTarget;
	bool	m_bFinish;
private:
	GameObject* m_player;
	Vector3 m_firstDir;
	float m_speed;
};

