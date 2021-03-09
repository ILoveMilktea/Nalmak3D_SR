#pragma once
#include "IState.h"
class State_Evasion_Airfire :
	public IState
{
public:
	State_Evasion_Airfire();
	~State_Evasion_Airfire();

	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

	void Wave_1();
	void Wave_2();

private:
	float m_spawnTimer;

	int m_spawnIndex;

	Vector3 m_spawnPos[8];
};

