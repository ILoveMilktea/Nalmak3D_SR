#pragma once
#include "Component.h"
class Enemy_MidBoss :
	public Component
{
public:
	enum MODE { AUTO, CONTROL };
	MODE m_mode;

public:
	struct Desc
	{
		Desc(ENEMY_STATUS _status)
		{
			tStatus = _status;
		}
		ENEMY_STATUS tStatus;

		GameObject* pivot = nullptr;
	};

public:
	Enemy_MidBoss(Desc* _desc);
	virtual ~Enemy_MidBoss();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;


public: /* Get */
	int		Get_FullHp() const;
	int		Get_CurHp() const;

	GameObject* GetBulletproofPivot() { return m_bulletproofPivot; }
public: /* Set */
	void PivotRotateOn() { m_pivotRotate = true; }
	void PivotRotateOff() { m_pivotRotate = false; }

public: /* Function */
	void Damaged(int _dmg);

private:
	ENEMY_STATUS m_status;

	GameObject* m_bulletproofPivot;
	bool m_pivotRotate;
};

