#pragma once

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Component.h"
#include "EventHandler.h"
#include "Event.h"
#include "Nalmak_Include.h"
class  NALMAK_DLL Button :
	public Component
{
public:
	struct Desc
	{
		EventHandler eventFunc;
	};
	Button(Desc* _desc);
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;

private:
	Event m_event;
	InputManager* m_input;

private:
	bool IsClick();
};

#endif