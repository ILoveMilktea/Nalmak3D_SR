#include "stdafx.h"
#include "UI_ShopMenu_Animator.h"

UI_ShopMenu_Animator::UI_ShopMenu_Animator(Desc * _desc)
{
	m_amount = _desc->amount;
	m_duration = _desc->duration;
}

UI_ShopMenu_Animator::~UI_ShopMenu_Animator()
{
}

void UI_ShopMenu_Animator::Initialize()
{
	m_scaleAnim.SetAnimation(IAnimation::LERP);
	m_colorAnim.SetAnimation(IAnimation::LERP);

	m_originScale = m_transform->scale;
	m_transform->scale = Vector3(0.f, 0.f, 0.f);
	m_isPlayingOffAnim = false;
}

void UI_ShopMenu_Animator::Update()
{
	if (m_isPlayingOffAnim)
	{
		if (!m_scaleAnim.IsPlay())
		{
			m_transform->scale = Vector3(0.f, 0.f, 0.f);
			m_isPlayingOffAnim = false;
		}
	}

	m_scaleAnim.Play_CurrentAnimation();
	m_colorAnim.Play_CurrentAnimation();
}

void UI_ShopMenu_Animator::OnAnim()
{
	FadeInAnim();
	ScaleUpAnim();
	m_transform->scale = Vector3(0.f, 0.f, 0.f);
}

void UI_ShopMenu_Animator::OffAnim()
{
	FadeOutAnim();
	ScaleDownAnim();
	m_isPlayingOffAnim = true;
}

void UI_ShopMenu_Animator::FadeInAnim()
{
	m_colorAnim.SetActor(m_gameObject);
	m_colorAnim.SetStartColor(Vector4(1.f, 1.f, 1.f, 0.5f));
	m_colorAnim.SetDestColor(Vector4(1.f, 1.f, 1.f, 1.f));
	m_colorAnim.SetPlayDuration(m_duration);
	m_colorAnim.SetStartDelay(m_delay);
	m_colorAnim.Start_Animation();
}

void UI_ShopMenu_Animator::FadeOutAnim()
{
	m_colorAnim.SetActor(m_gameObject);
	m_colorAnim.SetStartColor(Vector4(1.f, 1.f, 1.f, 1.f));
	m_colorAnim.SetDestColor(Vector4(1.f, 1.f, 1.f, 0.5f));
	m_colorAnim.SetPlayDuration(m_duration);
	m_colorAnim.SetStartDelay(m_delay);
	m_colorAnim.Start_Animation();
}

void UI_ShopMenu_Animator::ScaleUpAnim()
{
	m_scaleAnim.SetActor(m_gameObject);
	m_scaleAnim.SetStartScale(m_originScale * 0.8f);
	m_scaleAnim.SetDestScale(m_originScale);
	m_scaleAnim.SetPlayDuration(m_duration);
	m_scaleAnim.SetStartDelay(m_delay);
	m_scaleAnim.Start_Animation();
}

void UI_ShopMenu_Animator::ScaleDownAnim()
{
	m_scaleAnim.SetActor(m_gameObject);
	m_scaleAnim.SetStartScale(m_originScale);
	m_scaleAnim.SetDestScale(m_originScale * 0.8f);
	m_scaleAnim.SetPlayDuration(m_duration);
	m_scaleAnim.SetStartDelay(m_delay);
	m_scaleAnim.Start_Animation();
}

void UI_ShopMenu_Animator::SetAnimator(float _amount, float _duration, float _delay, Vector3 _pos)
{
	m_amount = _amount;
	m_duration = _duration;
	m_delay = _delay;
	SetPosition(_pos);
}
