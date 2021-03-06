#pragma once
#include "Component.h"

class UI_Alarm :
	public Component
{
public:
	enum ALARMTYPE { WARNING, NOTICE, KILL, MAX };

	struct Desc
	{
		ALARMTYPE type;
		GameObject* text;
		GameObject* light;

		Vector3 startPos = Vector3(1800.f, 300.f, 0.f);

		float on_moveAmount = 400.f;
		float on_duration = 1.f;

		float up_moveAmount = 40.f;
		float up_duration = 1.f;

		float off_moveAmount = 20.f;
		float off_duration = 1.f;
	};

public:
	UI_Alarm(Desc* _desc);
	~UI_Alarm();

	virtual void Initialize() override;
	virtual void Update() override;
		
	void AlarmOnAnim();	// moveIn + img bright
	void AlarmUpAnim(); // move up
	void AlarmOffAnim(); // fade out

	void Remove();

	bool IsPlay();

private:
	GameObject* m_text;
	GameObject* m_light;
	ALARMTYPE m_type;

	MoveAnimation m_moveAnim;
	ScaleAnimation m_scaleAnim;
	ColorAnimation m_colorAnim_ch1;
	ColorAnimation m_colorAnim_ch2;

	float m_on_moveAmount;
	float m_on_duration;

	float m_up_moveAmount;
	float m_up_duration;

	float m_off_moveAmount;
	float m_off_duration;
};

