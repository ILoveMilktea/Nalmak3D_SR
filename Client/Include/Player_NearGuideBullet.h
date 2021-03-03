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

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;

private:
	Vector3 m_firstTarget;

private:
	Vector3 m_firstDir;
	float m_speed;
};

