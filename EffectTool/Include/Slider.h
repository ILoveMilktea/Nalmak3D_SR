#pragma once
#ifndef __SLIDER_H__
#define __SLIDER_H__

#include "Component.h"

class Transform;
class NALMAK_DLL Slider :
	public Component
{
public:
	struct Desc
	{
		Transform* background = nullptr;
		Transform* fill = nullptr;

		const float* curValue = nullptr;
		const float* maxValue = nullptr;
	};

public:
	Slider(Desc* _desc);

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	
private:
	Transform* m_background;
	Transform* m_fill;
	float m_fillWidthOrigin;

	const float* m_curValue;
	const float* m_maxValue;

	float m_observeValue;
};


#endif // !__SLIDER_H__

