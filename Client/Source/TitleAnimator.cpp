#include "stdafx.h"
#include "..\Include\TitleAnimator.h"


TitleAnimator::TitleAnimator(Desc * _desc)
{
}

TitleAnimator::~TitleAnimator()
{
}

void TitleAnimator::Initialize()
{
	m_colorAnim_fadein.SetAnimation(IAnimation::LERP);
	m_colorAnim_fadeout.SetAnimation(IAnimation::LERP);
}

void TitleAnimator::Update()
{
	m_colorAnim_fadeout.Play_CurrentAnimation();
	if (m_animOn)
	{
		if (!m_colorAnim_fadeout.IsPlay())
		{
			GetComponent<Text>()->SetText(m_menuName);
			m_animOn = false;
		}
	}

	m_colorAnim_fadein.Play_CurrentAnimation();
}

void TitleAnimator::SetTitle_MainMenu()
{
	m_menuName = L"MAIN MENU";
	m_animOn = true;

	FadeInAnim();
	FadeOutAnim();
}

void TitleAnimator::SetTitle_Shop()
{
	m_menuName = L"SHOP";
	m_animOn = true;

	FadeInAnim();
	FadeOutAnim();
}

void TitleAnimator::SetTitle_Equip()
{
	m_menuName = L"EQUIP";
	m_animOn = true;

	FadeInAnim();
	FadeOutAnim();
}

void TitleAnimator::FadeInAnim()
{
	m_colorAnim_fadein.SetActor(m_gameObject);
	m_colorAnim_fadein.SetStartColor(Vector4(1.f, 1.f, 1.f, 0.f));
	m_colorAnim_fadein.SetDestColor(Vector4(1.f, 1.f, 1.f, 1.f));
	m_colorAnim_fadein.SetPlayDuration(m_duration * 0.5f);
	m_colorAnim_fadein.SetStartDelay(m_delay);
	m_colorAnim_fadein.Start_Animation();
}

void TitleAnimator::FadeOutAnim()
{
	m_colorAnim_fadeout.SetActor(m_gameObject);
	m_colorAnim_fadeout.SetStartColor(Vector4(1.f, 1.f, 1.f, 1.f));
	m_colorAnim_fadeout.SetDestColor(Vector4(1.f, 1.f, 1.f, 0.f));
	m_colorAnim_fadeout.SetPlayDuration(m_duration * 0.5f);
	m_colorAnim_fadeout.SetStartDelay(0.f);
	m_colorAnim_fadeout.Start_Animation();
}

void TitleAnimator::SetAnimator(float _amount, float _duration, float _delay, Vector3 _pos)
{
	m_amount = _amount;
	m_duration = _duration;
	m_delay = _delay;
	SetPosition(_pos);
}
