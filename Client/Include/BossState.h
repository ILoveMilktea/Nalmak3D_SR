#pragma once
#include "IState.h"
class BossState : public IState
{
public:
	BossState();
	~BossState();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public: /* Get */
	float Get_Time() const;
	float Get_Score() const;

public: /* Set */
	void Set_Score(float _score);
	void Add_Score(float _score);

public: /* Functions */

private:
	float	m_fBossTime = 0.f;
	float	m_fBossScore = 0.f;
};

