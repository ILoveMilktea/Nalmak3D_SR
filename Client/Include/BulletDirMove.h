#pragma once
#include "Component.h"
class BulletDirMove :
	public Component
{
public:
	struct Desc
	{
		float speed = 0.f;
	};
public:
	BulletDirMove(Desc* _desc);
	virtual ~BulletDirMove();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
private:
	GameObject* m_toTarget;
	Vector3 m_dir;
	float m_speed;
};

