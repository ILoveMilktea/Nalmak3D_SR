#pragma once
#include "IState.h"
class StageSelectCamera_Stage2 :
	public IState
{
public:
	StageSelectCamera_Stage2();
	~StageSelectCamera_Stage2();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

