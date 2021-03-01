#pragma once
#ifndef __ENEMYDETECTOR_H__
#define __ENEMYDETECTOR_H__

#include "Component.h"
class Camera;
class EnemyManager;
class EnemyDetector :
	public Component
{
public:

	enum AREA { NONE, LEFT_TOP, LEFT_BOTTOM, RIGHT_TOP, RIGHT_BOTTOM };
	struct Desc
	{
		float detectRectWidth = 480.f;
		float detectRectHeight = 480.f;
		float detectRange = 200.f;

		int readyTag = 10;

		GameObject* crosshair = nullptr;
	};

	struct NameTag
	{
		GameObject* text = nullptr;
		GameObject* image = nullptr;
		AREA area = NONE;
	};

public:
	EnemyDetector(Desc* _desc);
	~EnemyDetector();

private:
	virtual void Initialize() override;
	virtual void Update() override;

	void UpdateTarget();
	void SetNameTag();

	bool CheckArea_LT(const Vector2& _pos);
	bool CheckArea_LB(const Vector2& _pos);
	bool CheckArea_RT(const Vector2& _pos);
	bool CheckArea_RB(const Vector2& _pos);
	
	void CreateMoreTag(size_t _count);

private:
	EnemyManager* m_enemyManager = nullptr;
	Camera* m_mainCamera = nullptr;
	GameObject* m_detectRectImage = nullptr;

	GameObject* m_crosshair = nullptr;
	GameObject* m_lockonTarget = nullptr;
	int m_targetIndex;

	float m_detectRange;
	RECT m_detectRect;


	list<Vector2> m_enemyPoint;
	vector<NameTag> m_nametagContainer;

	float m_timer;
};


#endif // !__ENEMYDETECTOR_H__

