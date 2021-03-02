#pragma once
#include "IState.h"
class Circle_Evasion :
	public IState
{
public:
	Circle_Evasion();
	virtual ~Circle_Evasion();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

