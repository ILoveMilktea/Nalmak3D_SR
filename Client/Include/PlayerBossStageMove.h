#pragma once
#include "IState.h"
class PlayerBossStageMove :
	public IState
{
public:
	PlayerBossStageMove();
	virtual ~PlayerBossStageMove();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

