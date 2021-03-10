#pragma once
#include "IState.h"
class DogFight_Stage2_Enter :
	public IState
{
public:
	DogFight_Stage2_Enter();
	virtual ~DogFight_Stage2_Enter();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

