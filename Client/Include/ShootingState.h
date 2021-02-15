#pragma once
#include "IState.h"
class ShootingState :public IState
{
public:
	ShootingState();
	~ShootingState();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

