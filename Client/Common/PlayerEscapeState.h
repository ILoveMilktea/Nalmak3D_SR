#pragma once
#include "IState.h"
class PlayerEscapeState :
	public IState
{
public:
	PlayerEscapeState();
	virtual ~PlayerEscapeState();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	InputManager m_inputManager;
	class PlayerSkillActor* m_skillActor;
private:
	class PlayerItem* m_skillInfo;
	float m_dealy;
};
