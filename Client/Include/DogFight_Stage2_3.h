#pragma once
#include "IState.h"
class DogFight_Stage2_3 :
	public IState
{
public:
	DogFight_Stage2_3();
	virtual ~DogFight_Stage2_3();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

