#pragma once
#include "Component.h"
class TitleAnimator :
	public Component
{
public:
	struct Desc
	{
	};

public:
	TitleAnimator(Desc* _desc);
	~TitleAnimator();

	virtual void Initialize() override;
	virtual void Update() override;

	void SetTitle_MainMenu();
	void SetTitle_Shop();
	void SetTitle_Equip();

private:
	void FadeInAnim();
	void FadeOutAnim();

public:
	void SetAnimator(float _amount, float _duration, float _delay, Vector3 _pos);

private:
	ColorAnimation m_colorAnim_fadein;
	ColorAnimation m_colorAnim_fadeout;

	float m_amount;
	float m_duration;
	float m_delay;

	bool m_animOn;
	wstring m_menuName;
};

