#pragma once
#include "Component.h"
class UseItem :
	public Component
{

public:
	UseItem(ItemDesc* _desc);
	virtual ~UseItem();


protected:
	virtual void Initialize() override;
	virtual void Update() override;

public:
	virtual void Shooting() = 0;

protected:
	ITEMTYPE m_itemtype = {};
	float	m_useDelay = 0.f;
	float	m_shotSpeed = 0.f;
	int		 m_weaponAttak = 0;
	int		 m_weaponAmmo = 0;


};

