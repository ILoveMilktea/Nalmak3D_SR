#pragma once
#include "Component.h"
class Boss :
	public Component
{
public:
	struct Desc
	{
		Desc(ENEMY_STATUS _status)
		{
			tStatus = _status;
		}
		ENEMY_STATUS tStatus;
		

	};
public:
	Boss(Desc* _desc);
	virtual ~Boss();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release()override;
	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;

public: /* Get */
	int		Get_FullHp() const;
	int		Get_CurHp() const;

public: /* Set */
	

public: /* Function */
	void Damaged(int _dmg);

private: 
	ENEMY_STATUS m_tBossStatus;

};

