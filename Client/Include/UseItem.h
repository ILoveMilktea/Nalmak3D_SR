#pragma once
#include "Component.h"
class UseItem :
	public Component
{

public:
	UseItem(ItemDesc* _desc);
	virtual ~UseItem();


	virtual void Initialize() override;
	virtual void Update() override;

public:
	virtual void Shooting();

protected:
	ITEMTYPE m_itemtype;
	float	m_useDelay;
	float	m_shotSpeed;
	

};

