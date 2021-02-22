#pragma once
#ifndef __SINGLELINE_H__
#define __SINGLELINE_H__

#include "Component.h"
class Core;
class SingleLine :
	public Component
{
public:
	struct Desc
	{
		Vector3 point1;
		Vector3 point2;
	};

public:
	SingleLine(Desc* _desc);

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	
private:
	Core* m_core;
	Vector3 m_point1;
	Vector3 m_point2;
};


#endif // !__SINGLELINE_H__
