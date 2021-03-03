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


	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

private:
	Material* m_mtrl;
	Camera* m_cam;
};

