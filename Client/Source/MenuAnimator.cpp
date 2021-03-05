#include "stdafx.h"
#include "MenuAnimator.h"

MenuAnimator::MenuAnimator(Desc * _desc)
{
	m_amount = _desc->amount;
	m_duration = _desc->duration;
}

void MenuAnimator::Initialize()
{
	m_moveAnim.SetActor(m_gameObject);
	m_moveAnim.SetAnimation(IAnimation::LERP);
}

void MenuAnimator::Update()
{
	m_moveAnim.Play_CurrentAnimation();
}

void MenuAnimator::InAnim()
{
	m_moveAnim.SetActor(m_gameObject);
	m_moveAnim.SetStartPosition();
	m_moveAnim.SetDestPosition(Vector3(m_transform->position.x + m_amount, m_transform->position.y, 0.f));
	m_moveAnim.SetPlayDuration(m_duration);
	m_moveAnim.SetStartDelay(m_delay);
	m_moveAnim.Start_Animation();
}

void MenuAnimator::OutAnim()
{
	m_moveAnim.SetActor(m_gameObject);
	m_moveAnim.SetStartPosition();
	m_moveAnim.SetDestPosition(Vector3(m_transform->position.x - m_amount, m_transform->position.y, 0.f));
	m_moveAnim.SetPlayDuration(m_duration);
	m_moveAnim.SetStartDelay(m_delay);
	m_moveAnim.Start_Animation();
}
