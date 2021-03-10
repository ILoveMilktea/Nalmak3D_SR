#pragma once
#include "Component.h"
class SliderAnimator :
	public Component
{
public:
	struct Desc {

	};

	SliderAnimator(Desc* _desc);
	~SliderAnimator();

	virtual void Initialize() override;
	virtual void Update() override;

	void Refill(float _curValue, float _maxValue, float _duration = 0.5f);

	void Fill_MoveAnim();
	void Fill_ScaleAnim();

	void Slider_InAnim();
	void Slider_OutAnim();
	
	void SetInOutAnim(float _amount, float _duration, float _delay, Vector3 _startPos);
	
	void SetFill(GameObject* _fill);
private:
	GameObject* m_fill;

	MoveAnimation m_moveAnim_Slider;

	MoveAnimation m_moveAnim_Fill;
	ScaleAnimation m_scaleAnim;

	float m_inout_Amount;
	float m_inout_Duration;
	float m_inout_Delay;

	Vector3 m_fill_originLeft;
	float m_fill_originWidth;
	float m_fill_curValue;
	float m_fill_maxValue;
	float m_fill_Duration;
};

