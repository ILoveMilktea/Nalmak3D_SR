#pragma once
#include "Component.h"
class Boss :
	public Component
{
public:
	struct Desc
	{
		
	};
public:
	Boss(Desc* _desc);
	virtual ~Boss();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;

public: /* Get */

public: /* Set */

public: /* Function */

private: 

};

