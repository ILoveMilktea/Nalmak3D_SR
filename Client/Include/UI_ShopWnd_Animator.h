#pragma once
#include "Component.h"
class UI_ShopWnd_Animator :
	public Component
{
public:
	struct Desc
	{
		float longAmount = 100.f;
		float shortAmount = 10.f;
		float duration = 1.f;
	};

public:
	UI_ShopWnd_Animator(Desc* _desc);
	~UI_ShopWnd_Animator();

	virtual void Initialize() override;
	virtual void Update() override;

	void OnAnim();
	void OffAnim();

private:
	void MoveLongDownAnim();
	void MoveLongUpAnim();
	void MoveShortDownAnim();
	void MoveShortUpAnim();

	void MoveLongRightAnim();
	void MoveLongLeftAnim();
	void MoveShortRightAnim();
	void MoveShortLeftAnim();

public:
	void SetAnimator(float _longAmount, float _shortAmount, float _duration, float _delay, Vector3 _pos);

	void AddStartDelay(float _delay) { m_delay += _delay; }

private:
	MoveAnimation m_moveAnim_ch1;
	MoveAnimation m_moveAnim_ch2;

	float m_longAmount;
	float m_shortAmount;
	float m_duration;
	float m_delay;

	float m_timeRatio;

	Vector3 m_originPos;
};

