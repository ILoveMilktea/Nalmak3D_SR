#pragma once
#include "IState.h"
class PlayerTopViewMove :
	public IState
{
public:
	PlayerTopViewMove();
	virtual ~PlayerTopViewMove();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:
	void TopViewMoving();
private:

};

