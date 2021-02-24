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
		WeponType wepontype = NORMAL_MISSILE;
	};

public:
	UseKit(Desc* _desc);
	virtual ~UseKit();

public:
	virtual void Initialize() override;


private:
	WeponType m_eWeponType = WeponType::WEPON_END;
	float m_delay = 0.f;
	float m_kitAttack = 0.f;
	float m_kitSpeed = 0.f;



};

