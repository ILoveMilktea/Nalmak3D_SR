#pragma once
#include "IState.h"
class DogFight_Stage2_Exit :
	public IState
{
public:
	DogFight_Stage2_Exit();
	virtual ~DogFight_Stage2_Exit();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	int m_timer;
	
};

