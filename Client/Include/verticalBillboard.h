#pragma once
#include "Component.h"
class verticalBillboard :
	public Component
{
public:
	struct Desc
	{

	};
public:
	verticalBillboard(Desc* _desc);
	~verticalBillboard();


	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;

private:
	Material* m_mtrl;
	Camera* m_cam;
};

