#pragma once
#include "Component.h"
class Player_Missile :
	public Component
{
public:
	Player_Missile();
	~Player_Missile();
public:
	virtual void Create() = 0;
	virtual void Fly() = 0;
	virtual void Action() = 0;
	virtual void Bomb() = 0;



};

