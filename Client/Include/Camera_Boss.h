#pragma once
#include "IState.h"
class Camera_Boss :
	public IState
{
public:
	Camera_Boss();
	virtual ~Camera_Boss();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};

