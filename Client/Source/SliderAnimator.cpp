#include "stdafx.h"
#include "..\Include\SliderAnimator.h"



SliderAnimator::SliderAnimator(Desc * _desc)
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
	m_moveAnim_Slider.Play_CurrentAnimation();

	m_moveAnim_Fill.Play_CurrentAnimation();
	m_scaleAnim.Play_CurrentAnimation();
}

void SliderAnimator::Refill(float _curValue, float _maxValue, float _duration)
{
	m_fill_curValue = _curValue;
	m_fill_maxValue = _maxValue;
	m_fill_Duration = _duration;

	
	Fill_MoveAnim();
	Fill_ScaleAnim();
}

void SliderAnimator::Fill_MoveAnim()
{
	m_moveAnim_Slider.SetActor(m_gameObject);
	m_moveAnim_Slider.SetStartPosition(m_fill_originLeft);
	Vector3 dest = m_fill_originLeft;
	dest.x += m_fill_originWidth * (m_fill_curValue / m_fill_maxValue) * 0.5f;
	m_moveAnim_Slider.SetDestPosition(dest);
	m_moveAnim_Slider.SetPlayDuration(0.5f);
	m_moveAnim_Slider.SetStartDelay(0.f);
	m_moveAnim_Slider.Start_Animation();
}

void SliderAnimator::Fill_ScaleAnim()
{
	m_scaleAnim.SetActor(m_fill);
	Vector3 scale = Vector3(0.f, m_fill->GetTransform()->scale.y, 0.f);
	m_scaleAnim.SetStartScale(scale);
	scale.x += m_fill_originWidth * (m_fill_curValue / m_fill_maxValue);
	m_scaleAnim.SetDestScale(scale);
	m_scaleAnim.SetPlayDuration(0.5f);
	m_scaleAnim.SetStartDelay(0.f);
	m_scaleAnim.Start_Animation();
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

void SliderAnimator::SetFill(GameObject * _fill)
{
	m_fill = _fill;
	RECT* rt = _fill->GetComponent<CanvasRenderer>()->GetBoundary();
	m_fill_originWidth = float(rt->right - rt->left);
	m_fill_originLeft = Vector3(rt->left,(rt->top + rt->bottom) * 0.5f,0.f);
}
