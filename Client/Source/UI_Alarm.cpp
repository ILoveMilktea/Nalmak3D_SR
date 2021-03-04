#include "stdafx.h"
#include "..\Include\UI_Alarm.h"


UI_Alarm::UI_Alarm(Desc* _desc)
{
	m_type = _desc->type;
	m_text = _desc->text;
	m_light = _desc->light;

	m_moveAnim.SetActor(m_text);
	m_scaleAnim.SetActor(m_text);
	m_colorAnim_ch1.SetActor(m_light);
	m_colorAnim_ch2.SetActor(m_light);

	m_on_moveAmount = _desc->on_moveAmount;
	m_on_duration = _desc->on_moveAmount;
}


UI_Alarm::~UI_Alarm()
{
}

void UI_Alarm::Initialize()
{
}

void UI_Alarm::Update()
{
	m_moveAnim.Play_CurrentAnimation();
	m_scaleAnim.Play_CurrentAnimation();
	m_colorAnim_ch1.Play_CurrentAnimation();
	m_colorAnim_ch2.Play_CurrentAnimation();
}

void UI_Alarm::AlarmOnAnim()
{
	// text move left
	m_moveAnim.SetStartPosition();
	m_moveAnim.SetDestPosition(Vector3(m_transform->position.x + m_on_moveAmount, m_transform->position.y, 0.f));
	m_moveAnim.SetPlayDuration(m_on_duration);
	m_moveAnim.Start_Animation();
	// text scale up
	m_scaleAnim.SetStartScale(Vector3(0.f, m_transform->scale.y, 0.f));
	m_scaleAnim.SetDestScale(Vector3(200.f, m_transform->scale.y, 0.f));
	m_scaleAnim.SetPlayDuration(m_on_duration);
	m_scaleAnim.Start_Animation();

	Vector4 color;
	switch (m_type)
	{
	case UI_Alarm::WARNING:
		color = Vector4(1.f, 1.f, 0.f, 0.f);
		break;
	case UI_Alarm::NOTICE:
		color = Vector4(0.f, 1.f, 0.f, 0.f);
		break;
	case UI_Alarm::KILL:
		color = Vector4(1.f, 0.f, 0.f, 0.f);
		break;
	}
	// img light (fade in -> fade out)
	m_colorAnim_ch1.SetStartColor(color);
	m_colorAnim_ch1.SetDestColor(color + Vector4(0.f, 0.f, 0.f,1.f));
	m_colorAnim_ch1.SetPlayDuration(m_on_duration * 0.5f);
	m_colorAnim_ch1.Start_Animation();
	// img light (fade out -> fade in)
	m_colorAnim_ch2.SetStartColor(color + Vector4(0.f, 0.f, 0.f, 1.f));
	m_colorAnim_ch2.SetDestColor(color);
	m_colorAnim_ch2.SetPlayDuration(0.5f);
	m_colorAnim_ch2.SetStartDelay(m_on_duration * 0.5f);
	m_colorAnim_ch2.Start_Animation();
}

void UI_Alarm::AlarmUpAnim()
{
	// move up
	m_moveAnim.SetStartPosition();
	m_moveAnim.SetDestPosition(Vector3(m_transform->position.x, m_transform->position.y - m_up_moveAmount, 0.f));
	m_moveAnim.SetPlayDuration(m_up_duration);
	m_moveAnim.Start_Animation();
}

void UI_Alarm::AlarmOffAnim()
{
	// text up a little
	m_moveAnim.SetStartPosition();
	m_moveAnim.SetDestPosition(Vector3(m_transform->position.x, m_transform->position.y - m_off_moveAmount, 0.f));
	m_moveAnim.SetPlayDuration(m_off_duration);
	m_moveAnim.Start_Animation();
	// text fadeout
	m_colorAnim_ch1.SetActor(m_text);
	m_colorAnim_ch1.SetStartColor(Vector4(1.f, 1.f, 1.f, 1.f));
	m_colorAnim_ch1.SetDestColor(Vector4(1.f, 1.f, 1.f, 0.f));
	m_colorAnim_ch1.SetPlayDuration(m_off_duration);
	m_colorAnim_ch1.Start_Animation();
}
