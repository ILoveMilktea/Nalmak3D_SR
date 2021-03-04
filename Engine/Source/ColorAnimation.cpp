#include "..\Include\ColorAnimation.h"
#include "CanvasRenderer.h"


ColorAnimation::ColorAnimation()
{
}


ColorAnimation::~ColorAnimation()
{
}

void ColorAnimation::Start_Animation()
{
	IAnimation::Start_Animation();
}

bool ColorAnimation::Play_CurrentAnimation()
{
	if (!IAnimation::Play_CurrentAnimation())
		return false;

	return true;
}

void ColorAnimation::End_Animation()
{
	IAnimation::End_Animation();

	m_actor->GetComponent<CanvasRenderer>()->SetColor(m_destColor);
}

void ColorAnimation::Play_Lerp()
{
	Vector4 curColor;
	float curTime = (m_playTimer - m_startDelay) / m_playDuration;
	D3DXVec4Lerp(&curColor, &m_startColor, &m_destColor, curTime);

	m_actor->GetComponent<CanvasRenderer>()->SetColor(curColor);
}

void ColorAnimation::Play_Custom()
{
}

void ColorAnimation::SetStartColor()
{
	m_startColor = m_actor->GetComponent<CanvasRenderer>()->GetColor();
}

void ColorAnimation::SetStartColor(Vector4 _color)
{
	m_actor->GetComponent<CanvasRenderer>()->SetColor(_color);
	m_startColor = _color;
}