#pragma once
#include "Component.h"
class MoveDebuger :
	public Component
{
public:
	struct Desc
	{

	};
public:
	MoveDebuger(Desc* _desc);
	~MoveDebuger();

	virtual void Initialize() override;
	virtual void Update() override;
};

