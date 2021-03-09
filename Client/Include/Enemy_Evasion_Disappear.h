#pragma once
#include "IState.h"
class Enemy_Evasion_Disappear :
	public IState
{
public:
	Enemy_Evasion_Disappear();
	~Enemy_Evasion_Disappear();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

	void SetDestPos(Vector3 _pos) { m_destPos = _pos; }

private:
	float m_timer;

	Vector3 m_startPos;
	Vector3 m_destPos;
	wstring m_nextState;
};

