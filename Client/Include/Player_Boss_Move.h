#pragma once
#include "IState.h"
class Player_Boss_Move :
	public IState
{
public:
	Player_Boss_Move();
	virtual ~Player_Boss_Move();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

