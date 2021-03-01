#pragma once
#ifndef __CROSSHAIR_H__
#define __CROSSHAIR_H__


#include "SingleImage.h"
class Crosshair :
	public SingleImage
{
public:
	struct Desc
	{
		SingleImage::Desc img_desc = SingleImage::Desc();

		float width = 480.f;
		float height = 480.f;
	};

public:
	Crosshair(Desc* _desc);

public:
	void UpdatePosition(SetVector2Func _setValueFunc, GetVector2Func _getValueFunc);

	float m_width;
	float m_height;
	Vector2 m_mousePosition;
	RECT m_limitBoundary;
};



#endif // !__CROSSHAIR_H__
