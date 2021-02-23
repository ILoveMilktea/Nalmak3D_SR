#pragma once
#ifndef __PAUSESTATE_H__
#define __PAUSESTATE_H__


#include "IState.h"
class PauseState :
	public IState
{
public:
	PauseState();
	~PauseState();



	// IState을(를) 통해 상속됨
	virtual void Initialize() override;

	virtual void EnterState() override;

	virtual void UpdateState() override;

	virtual void ExitState() override;

};


#endif // !__PAUSESTATE_H__
