#pragma once
#include "Component.h"
class NALMAK_DLL AutoRotate :
	public Component
{
public:
	struct Desc
	{
		float xAxisSpeed = 0;
		float yAxisSpeed = 0;
		float zAxisSpeed = 0;
	};
public:
	AutoRotate(Desc* _desc);
	~AutoRotate();
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

	float m_xAxisSpeed = 0;
	float m_yAxisSpeed = 0;
	float m_zAxisSpeed = 0;

};

