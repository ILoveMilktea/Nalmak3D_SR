#pragma once
#include "IState.h"
class StageSelectCamera_Stage1 :
	public IState
{
public:
	StageSelectCamera_Stage1();
	~StageSelectCamera_Stage1();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

