#pragma once
#include "Component.h"
class UseKit :
	public Component
{

public:
	enum WeponType { NORMAL_MISSILE, GUID_MISSILE, CANNON_30MM, CANNON_20MM, WEPON_END };
	struct Desc
	{
		float delay = 0.f;
		float kitAttack = 0.f;
		float kitSpeed = 0.f;
		WeponType wepontype = WeponType::WEPON_END;
	};

public:
	UseKit(Desc* _desc);
	virtual ~UseKit();

public:
	virtual void Initialize() override;
	virtual void Update() override;

private:
	WeponType m_eWeponType = WeponType::WEPON_END;
	float m_delay = 0.f;
	float m_kitAttack = 0.f;
	float m_kitSpeed = 0.f;




	

};

