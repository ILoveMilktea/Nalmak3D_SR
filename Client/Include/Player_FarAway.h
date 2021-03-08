#pragma once
#include "IState.h"
class Player_FarAway :
	public IState
{
public:
	Player_FarAway();
	virtual ~Player_FarAway();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:
	void Check();
public:

private:
	float m_fSpd = 0.f;

};

