#pragma once
#ifndef __RADER_H__
#define __RADER_H__

#include "Component.h"

class EnemyManager;
class PlayerInfoManager;
class Rader :
	public Component
{
public:
	struct Desc
	{
		float findRange = 100.f;

		int readyIcon = 30;
	};

public:
	Rader(Desc* _desc);
	~Rader();

private:
	virtual void Initialize() override;
	virtual void Update() override;

	//void RotateStick();
	void UpdateTarget();
	void SetFlightPoint();

	void CreateMoreIcon(size_t _count);

private:
	GameObject* m_circleBackground = nullptr;		// ���̴� ���
	GameObject* m_circleMask = nullptr;				// ���̴� ����ũ
	GameObject* m_playerIcon = nullptr;				// �߽� �÷��̾� ��ü
	GameObject* m_stick = nullptr;					// �����
	GameObject* m_pivot = nullptr;		

	PlayerInfoManager* m_playerInfoManager = nullptr;
	EnemyManager* m_enemyManager = nullptr;

	list<Vector2> m_iconPoint;
	list<GameObject*> m_stickTrail;
	vector<GameObject*> m_IconContainer;
	float m_findRange;

	float m_findLineAngle;
	float m_timer;
};


#endif // !__RADER_H__
