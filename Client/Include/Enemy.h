#pragma once
#include "Component.h"
class Enemy :
	public Component
{
public:
	struct Desc 
	{
		
	};
public:
	Enemy(Desc* _Desc);
	virtual ~Enemy();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;


public:


public: /* Pattern */

private:

	
};

