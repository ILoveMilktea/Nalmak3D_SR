#pragma once
#ifndef __MOVEANIMATION_H__
#define __MOVEANIMATION_H__

#include "IAnimation.h"

class GameObject;
class NALMAK_DLL MoveAnimation :
	public IAnimation
{
public:
	MoveAnimation();
	~MoveAnimation();

public:
	virtual void Start_Animation() override;
	virtual bool Play_CurrentAnimation() override;
	virtual void End_Animation() override;

	virtual void Play_Lerp() override;
	virtual void Play_Custom() override;


public:
	void SetStartPosition();
	void SetStartPosition(Vector3 _start);
	void SetDestPosition(Vector3 _dest) { m_destPos = _dest; }

private:
	Vector3 m_startPos;
	Vector3 m_destPos;
};


#endif // !__MOVEANIMATION_H__
