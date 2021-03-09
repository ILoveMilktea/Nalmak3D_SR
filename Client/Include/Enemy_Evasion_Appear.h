#pragma once
#include "IState.h"
class Enemy_Evasion_Appear :
	public IState
{
public:
	Enemy_Evasion_Appear();
	~Enemy_Evasion_Appear();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

	void SetStartPos(Vector3 _pos) { m_startPos = _pos; }
	void SetDestPos(Vector3 _pos) { m_destPos = _pos; }
	void SetNextState(const wstring& _state) { m_nextState = _state; }

private:
	float m_timer;

	Vector3 m_startPos;
	Vector3 m_destPos;
	wstring m_nextState;
};

