#pragma once
#include "IState.h"
class CrossFire_Evasion :
	public IState
{
public:
	CrossFire_Evasion();
	virtual ~CrossFire_Evasion();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

