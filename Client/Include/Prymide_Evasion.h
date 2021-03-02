#pragma once
#include "IState.h"
class Prymide_Evasion :
	public IState
{
public:
	Prymide_Evasion();
	virtual ~Prymide_Evasion();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:

};

