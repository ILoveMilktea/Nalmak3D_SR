#include "stdafx.h"
#include "..\Include\SliderAnimator.h"


SliderAnimator::SliderAnimator()
{
}


SliderAnimator::~SliderAnimator()
{
}

void SliderAnimator::Initialize()
{
	m_moveAnim_Slider.SetActor(m_gameObject);
	m_moveAnim_Slider.SetAnimation(IAnimation::LERP);

	m_moveAnim_Fill.SetActor(m_gameObject);
	m_moveAnim_Fill.SetAnimation(IAnimation::LERP);

	m_scaleAnim.SetActor(m_gameObject);
	m_scaleAnim.SetAnimation(IAnimation::LERP);
}

void SliderAnimator::Update()
{
}

void SliderAnimator::Refill(float _curValue, float _maxValue, float _duration)
{
	m_fill_curValue = _curValue;
	m_fill_maxValue = _maxValue;
	m_fill_Duration = _duration;

	

}

void SliderAnimator::Fill_MoveAnim()
{

}

void SliderAnimator::Fill_ScaleAnim()
{

}

void SliderAnimator::Slider_InAnim()
{
	m_moveAnim_Slider.SetActor(m_gameObject);
	m_moveAnim_Slider.SetStartPosition();
	m_moveAnim_Slider.SetDestPosition(Vector3(m_transform->position.x + m_inout_Amount, m_transform->position.y, 0.f));
	m_moveAnim_Slider.SetPlayDuration(m_inout_Duration);
	m_moveAnim_Slider.SetStartDelay(m_inout_Delay);
	m_moveAnim_Slider.Start_Animation();
}

void SliderAnimator::Slider_OutAnim()
{
	m_moveAnim_Slider.SetActor(m_gameObject);
	m_moveAnim_Slider.SetStartPosition();
	m_moveAnim_Slider.SetDestPosition(Vector3(m_transform->position.x - m_inout_Amount, m_transform->position.y, 0.f));
	m_moveAnim_Slider.SetPlayDuration(m_inout_Duration);
	m_moveAnim_Slider.SetStartDelay(m_inout_Delay);
	m_moveAnim_Slider.Start_Animation();
}

void SliderAnimator::SetInOutAnim(float _amount, float _duration, float _delay, Vector3 _startPos)
{
	m_inout_Amount = _amount;
	m_inout_Duration = _duration;
	m_inout_Delay = _delay;
	SetPosition(_startPos);
}
