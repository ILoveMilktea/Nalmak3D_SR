#pragma once
#include "IState.h"
class DogFight_Stage1_Exit :
	public IState
{
public:
	DogFight_Stage1_Exit();
	virtual ~DogFight_Stage1_Exit();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

