#pragma once
#include "Component.h"
class Player :
	public Component
{
public:
	struct Desc 
	{


	};
public:
	Player(Desc* _desc);
	virtual ~Player();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;

public: /* Get */

public: /* Set */

public: /* Function */

private:

};

