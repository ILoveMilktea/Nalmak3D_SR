#include "..\Include\Slider.h"

#include "Transform.h"
#include "SingleImage.h"

Slider::Slider(Desc * _desc)
{
	m_background = _desc->background;
	m_fill = _desc->fill;
	
	m_curValue = _desc->targetValue;
	m_maxValue = _desc->maxValue;
}

void Slider::Initialize()
{
	m_fillWidthOrigin = m_fill->scale.x;
	m_observeValue = m_maxValue;
}

void Slider::Update()
{
	if (m_observeValue != *m_curValue)
	{
		float fillRatio = (*m_curValue) / (m_maxValue);
		float newWidth = m_fillWidthOrigin * fillRatio;
		float widthDifference = m_fill->scale.x - newWidth;
		m_fill->position.x -= widthDifference * 0.5f;
		m_fill->scale.x = newWidth;

		m_observeValue = *m_curValue;
	}

}
