#pragma once
#include "IState.h"
class Evasion :
	public IState
{
public:
	Evasion();
	virtual ~Evasion();

	// IState을(를) 통해 상속됨
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

