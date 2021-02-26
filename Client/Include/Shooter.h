#pragma once
#include "Component.h"
class Shooter :
	public Component
{



public:
	struct Desc
	{

	};

	Shooter(Desc * _desc);
	virtual ~Shooter();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;


	void ShooterActive(bool _activeCheck);

private:


};

