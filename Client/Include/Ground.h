#pragma once
#include "Component.h"
class Ground :
	public Component
{
public:
	struct Desc
	{

	};
public:
	Ground(Desc* _desc);
	~Ground();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
private:
	Material* m_groundMtrl;
};

