#pragma once
#include "IState.h"
class PlayerEscapeState :
	public IState
{
public:
	PlayerEscapeState();
	virtual ~PlayerEscapeState();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	InputManager* m_inputManager;
	class PlayerSkillActor* m_skillActor;
private:
	class PlayerItem* m_skillInfo;
	float m_dealy;

private:
	GameObject* m_temproryObj;

private:
	PlayerInfoManager* m_playerInfo;
	class MouseOption* m_mouse;
	float m_accel = 0.f;
};

