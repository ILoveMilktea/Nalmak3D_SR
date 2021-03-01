#pragma once
#include "IState.h"
class PlayerIdle :
	public IState
{
public:
	PlayerIdle();
	virtual ~PlayerIdle();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	InputManager* m_inputManager;
	class PlayerInfoManager* m_playerInfoManager;
	TimeManager* m_timeManager;

private:
	StateControl* m_stateControl;
};

