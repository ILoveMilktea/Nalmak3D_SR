#pragma once
#ifndef __CUSTOMDEBUGER_H__
#define __CUSTOMDEBUGER_H__

#include "Component.h"
class CustomDebuger :
	public Component
{
public:
	struct Desc
	{

	};
public:
	CustomDebuger(Desc* _desc);

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
};


#endif // !__CUSTOMDEBUGER_H__

