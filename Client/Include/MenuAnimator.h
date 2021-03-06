#pragma once
#ifndef __MENUANIMATOR_H__
#define __MENUANIMATOR_H__

#include "Component.h"
class MenuAnimator :
	public Component
{
public:
	struct Desc
	{
		float amount = 100.f;
		float duration = 1.f;
	};

public:
	MenuAnimator(Desc* _desc);

	virtual void Initialize() override;
	virtual void Update() override;

	void InAnim();
	void OutAnim();

	void SetAnimator(float _amount, float _duration, float _delay, Vector3 _pos);

	void SetMoveAmount(float _amount) { m_amount = _amount; }
	void SetMoveDuration(float _duration) { m_duration = _duration; }
	void SetStartDelay(float _delay) { m_delay = _delay; }

	void AddStartDelay(float _delay) { m_delay += _delay; }

private:
	MoveAnimation m_moveAnim;

	float m_amount;
	float m_duration;
	float m_delay;
};


#endif // !__MENUANIMATOR_H__
