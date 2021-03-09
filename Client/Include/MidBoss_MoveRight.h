#pragma once
#include "IState.h"
class MidBoss_MoveRight :
	public IState
{
public:
	MidBoss_MoveRight();
	~MidBoss_MoveRight();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

	void Move();
	void Spawn();

private:
	float m_moveTimer;
	float m_spawnTimer;
	float m_stateTimer;

	bool m_wave1;
	float m_spawnTerm;
	float m_stateDuration;

	Vector3 m_startPos;
	Vector3 m_destPos;
};

