#include "stdafx.h"
#include "UI_ShopWnd_Animator.h"


UI_ShopWnd_Animator::UI_ShopWnd_Animator(Desc * _desc)
{
	m_longAmount = _desc->longAmount;
	m_shortAmount = _desc->shortAmount;
	m_duration = _desc->duration;

	m_timeRatio = 0.8f;
}

UI_ShopWnd_Animator::~UI_ShopWnd_Animator()
{
}

void UI_ShopWnd_Animator::Initialize()
{
	m_moveAnim_ch1.SetAnimation(IAnimation::LERP);
	m_moveAnim_ch2.SetAnimation(IAnimation::LERP);

	m_originPos = m_transform->position;
}

void UI_ShopWnd_Animator::Update()
{
	m_moveAnim_ch1.Play_CurrentAnimation();
	m_moveAnim_ch2.Play_CurrentAnimation();
}

void UI_ShopWnd_Animator::OnAnim()
{
	//MoveLongDownAnim();
	//MoveShortUpAnim();

	MoveLongLeftAnim();
	//MoveShortRightAnim();
	m_transform->position = m_originPos;
}

void UI_ShopWnd_Animator::OffAnim()
{
	//MoveLongUpAnim();
	//MoveShortDownAnim();
	MoveLongRightAnim();
	//MoveShortLeftAnim();
}

void UI_ShopWnd_Animator::MoveLongDownAnim()
{
	m_moveAnim_ch1.SetActor(m_gameObject);
	m_moveAnim_ch1.SetStartPosition(m_originPos);
	m_moveAnim_ch1.SetDestPosition(m_originPos + Vector3(0.f, m_longAmount + m_shortAmount, 0.f));
	m_moveAnim_ch1.SetPlayDuration(m_duration * m_timeRatio);
	m_moveAnim_ch1.SetStartDelay(0.f);
	m_moveAnim_ch1.Start_Animation();
}

void UI_ShopWnd_Animator::MoveLongUpAnim()
{
	m_moveAnim_ch1.SetActor(m_gameObject);
	m_moveAnim_ch1.SetStartPosition(m_originPos + Vector3(0.f, m_longAmount + m_shortAmount, 0.f));
	m_moveAnim_ch1.SetDestPosition(m_originPos);
	m_moveAnim_ch1.SetPlayDuration(m_duration * m_timeRatio);
	m_moveAnim_ch1.SetStartDelay(m_duration * (1.f - m_timeRatio));
	m_moveAnim_ch1.Start_Animation();
}

void UI_ShopWnd_Animator::MoveShortDownAnim()
{
	m_moveAnim_ch2.SetActor(m_gameObject);
	m_moveAnim_ch2.SetStartPosition(m_originPos + Vector3(0.f, m_longAmount, 0.f));
	m_moveAnim_ch2.SetDestPosition(m_originPos + Vector3(0.f, m_longAmount + m_shortAmount, 0.f));
	m_moveAnim_ch2.SetPlayDuration(m_duration * (1.f - m_timeRatio));
	m_moveAnim_ch2.SetStartDelay(0.f);
	m_moveAnim_ch2.Start_Animation();
}

void UI_ShopWnd_Animator::MoveShortUpAnim()
{
	m_moveAnim_ch2.SetActor(m_gameObject);
	m_moveAnim_ch2.SetStartPosition(m_originPos + Vector3(0.f, m_longAmount + m_shortAmount, 0.f));
	m_moveAnim_ch2.SetDestPosition(m_originPos + Vector3(0.f, m_longAmount, 0.f));
	m_moveAnim_ch2.SetPlayDuration(m_duration * (1.f - m_timeRatio));
	m_moveAnim_ch2.SetStartDelay(m_duration * m_timeRatio);
	m_moveAnim_ch2.Start_Animation();
}

void UI_ShopWnd_Animator::MoveLongRightAnim()
{
	m_moveAnim_ch1.SetActor(m_gameObject);
	m_moveAnim_ch1.SetStartPosition(m_originPos + Vector3(m_longAmount + m_shortAmount, 0.f, 0.f));
	m_moveAnim_ch1.SetDestPosition(m_originPos);
	//m_moveAnim_ch1.SetPlayDuration(m_duration * m_timeRatio);
	m_moveAnim_ch1.SetPlayDuration(m_duration);
	//m_moveAnim_ch1.SetStartDelay(m_duration * (1.f - m_timeRatio));
	m_moveAnim_ch1.SetStartDelay(0.f);
	m_moveAnim_ch1.Start_Animation();
}

void UI_ShopWnd_Animator::MoveLongLeftAnim()
{
	//in
	m_moveAnim_ch1.SetActor(m_gameObject);
	m_moveAnim_ch1.SetStartPosition(m_originPos);
	m_moveAnim_ch1.SetDestPosition(m_originPos + Vector3(m_longAmount + m_shortAmount, 0.f, 0.f));
	//m_moveAnim_ch1.SetPlayDuration(m_duration * m_timeRatio);
	m_moveAnim_ch1.SetPlayDuration(m_duration);
	m_moveAnim_ch1.SetStartDelay(0.f);
	m_moveAnim_ch1.Start_Animation();
}

void UI_ShopWnd_Animator::MoveShortRightAnim()
{
	//in
	m_moveAnim_ch2.SetActor(m_gameObject);
	m_moveAnim_ch2.SetStartPosition(m_originPos + Vector3(m_longAmount + m_shortAmount, 0.f, 0.f));
	m_moveAnim_ch2.SetDestPosition(m_originPos + Vector3(m_longAmount, 0.f, 0.f));
	m_moveAnim_ch2.SetPlayDuration(m_duration * (1.f - m_timeRatio));
	m_moveAnim_ch2.SetStartDelay(m_duration * m_timeRatio);
	m_moveAnim_ch2.Start_Animation();
}

void UI_ShopWnd_Animator::MoveShortLeftAnim()
{
	m_moveAnim_ch2.SetActor(m_gameObject);
	m_moveAnim_ch2.SetStartPosition(m_originPos + Vector3(m_longAmount, 0.f, 0.f));
	m_moveAnim_ch2.SetDestPosition(m_originPos + Vector3(m_longAmount + m_shortAmount, 0.f, 0.f));
	m_moveAnim_ch2.SetPlayDuration(m_duration * (1.f - m_timeRatio));
	m_moveAnim_ch2.SetStartDelay(0.f);
	m_moveAnim_ch2.Start_Animation();
}


void UI_ShopWnd_Animator::SetAnimator(float _longAmount, float _shortAmount, float _duration, float _delay, Vector3 _pos)
{
	m_longAmount = _longAmount;
	m_shortAmount = _shortAmount;
	m_duration = _duration;
	m_delay = _delay;
	SetPosition(_pos);
}
