#pragma once
#include "IState.h"
class StageSelectCamera_Intro :
	public IState
{
public:
	StageSelectCamera_Intro();
	~StageSelectCamera_Intro();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;


};

