#pragma once

#ifndef __POSITIONHANDLE_H__
#define __POSITIONHANDLE_H__

#include "Component.h"
class Camera;
class Transform;
class InputManager;
class NALMAK_DLL PositionHandle :
	public Component
{
public:
	enum DIR { RIGHT,UP,FORWARD };
public:
	struct Desc
	{
		DIR dir;
	};
	PositionHandle(Desc* _desc);


public:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

public:
	void MoveTarget();
	void ActHandle(bool _value) { m_act = _value; }
	bool CheckActive() { return m_act; }

public:
	Transform* m_target;
	InputManager* m_input;
	Camera* m_camera;
	DIR m_moveDir;

	bool m_act;
};



#endif // !__POSITIONHANDLE_H__