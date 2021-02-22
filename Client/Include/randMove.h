#pragma once
#include "Component.h"
class randMove :
	public Component
{
	/* for Testing Class*/

public:
	struct Desc
	{
		float fSpd = 0.f; 

	};
public:
	randMove(Desc* _desc);
	virtual ~randMove();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	
private:
	float m_fSpd = 0.f;
};

