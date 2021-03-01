#pragma once
#ifndef __BOSSUIANIMATOR_H__
#define __BOSSUIANIMATOR_H__

#include "Component.h"
class BossUIAnimator :
	public Component
{
public:
	struct Desc
	{

	};

public:
	BossUIAnimator(Desc* _desc);

	virtual void Initialize() override;
	virtual void Update() override;

	void StartMoveDown(float _amount);
	void StartMoveUp(float _amount);

private:
	MoveAnimation m_moveAnim;
};

#endif // !__SLIDERANIMATOR_H__

