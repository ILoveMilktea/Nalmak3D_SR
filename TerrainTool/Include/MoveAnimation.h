#pragma once
#ifndef __MOVEANIMATION_H__
#define __MOVEANIMATION_H__

#include "IAnimation.h"

class GameObject;
class NALMAK_DLL MoveAnimation :
	public IAnimation
{
public:
	enum ANIMATION { LERP, CUSTOM };

public:
	MoveAnimation();
	~MoveAnimation();

public:
	virtual void Start_Animation() override;
	virtual bool Play_CurrentAnimation() override;
	virtual void End_Animation() override;

	void Play_MoveLerp();
	void Play_MoveCustom();

	void SetAnimation(ANIMATION _animation);

public:
	void SetActor(GameObject* _actor);
	void SetDestination(Vector3 _dest) { m_destination = _dest; }
	void SetPlaytime(float _time) { m_playTimer = _time; }

private:
	ANIMATION m_currentAnimation;
	GameObject* m_actor;

	Vector3 m_start;
	Vector3 m_destination;
};


#endif // !__MOVEANIMATION_H__
