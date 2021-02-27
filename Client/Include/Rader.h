#pragma once
#include "Component.h"

class PlayerInfoManager;
class Rader :
	public Component
{
public:
	struct Desc
	{
		float findRange = 25.f;

		int readyflight = 10;
	};

public:
	Rader(Desc* _desc);

private:
	virtual void Initialize() override;
	virtual void Update() override;

	void RotateStick();
	void UpdateTarget();
	void SetFlightPoint();
public:
	void Temp_AddEnemy(Transform* _tr) { m_enemy.emplace_back(_tr); }
	//void CheckEnemyInRange(GameO)

private:
	GameObject* m_circleBackground = nullptr;		// ���̴� ���
	GameObject* m_circleMask = nullptr;				// ���̴� ����ũ
	GameObject* m_playerIcon = nullptr;				// �߽� �÷��̾� ��ü
	GameObject* m_stick = nullptr;					// �����

	PlayerInfoManager* m_playerInfoManager = nullptr;

	list<Transform*> m_enemy;
	list<Vector2> m_iconPoint;
	list<GameObject*> m_stickTrail;
	vector<GameObject*> m_IconContainer;
	float m_findRange;

	float m_findLineAngle;
	float m_timer;
};

