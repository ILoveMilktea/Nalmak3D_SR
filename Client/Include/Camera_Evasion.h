#pragma once
#include "IState.h"
class Camera_Evasion :
	public IState
{
public:
	Camera_Evasion();
	virtual ~Camera_Evasion();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:
	
};

