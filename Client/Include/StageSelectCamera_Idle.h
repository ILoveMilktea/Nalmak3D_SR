#pragma once
#include "IState.h"
class StageSelectCamera_Idle :
	public IState
{
public:
	StageSelectCamera_Idle();
	~StageSelectCamera_Idle();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

