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

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;


	void ShooterActive(bool _activeCheck);

private:


};

