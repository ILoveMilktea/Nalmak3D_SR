#pragma once
#include "Component.h"
class PrintInfo :
	public Component
{
public:
	struct Desc
	{

	};
public:
	PrintInfo(Desc* _desc);
	~PrintInfo();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
};

