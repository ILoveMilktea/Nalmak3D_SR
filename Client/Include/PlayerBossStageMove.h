#pragma once
#include "IState.h"
class PlayerBossStageMove :
	public IState
{
public:
	PlayerBossStageMove();
	virtual ~PlayerBossStageMove();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public: /* Get */

public: /* Set */

public: /* function */
	void Accelerate();
private:
	float m_fSpd = 0.f;


};

