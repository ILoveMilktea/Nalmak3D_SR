#pragma once
#include "IState.h"
class EvasionState :
	public IState
{
public:
	EvasionState();
	virtual ~EvasionState();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:
	void EnterProduce();

private:
	GameObject* m_MainCamera = nullptr;
	GameObject* m_Player = nullptr;

	bool m_bEnter = false;
};

