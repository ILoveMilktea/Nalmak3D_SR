#pragma once

#include "Component.h"
class UI_ShopMenu_Animator :
	public Component
{

public:
	struct Desc
	{
		float amount = 100.f;
		float duration = 1.f;
	};

public:
	UI_ShopMenu_Animator(Desc* _desc);
	~UI_ShopMenu_Animator();

	virtual void Initialize() override;
	virtual void Update() override;

	void OnAnim();
	void OffAnim();

private:
	void FadeInAnim();
	void FadeOutAnim();
	void ScaleUpAnim();
	void ScaleDownAnim();

public:
	void SetAnimator(float _amount, float _duration, float _delay, Vector3 _pos);

	void AddStartDelay(float _delay) { m_delay += _delay; }

private:
	ScaleAnimation m_scaleAnim;
	ColorAnimation m_colorAnim;

	bool m_isPlayingOffAnim;

	float m_amount;
	float m_duration;
	float m_delay;
	Vector3 m_originScale;
};

