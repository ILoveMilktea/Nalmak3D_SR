#pragma once
#include "IState.h"
class EvasionState :
	public IState
{
public:
	EvasionState();
	virtual ~EvasionState();

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

public:
	void EnterProduce();

	void SceneToBoss();

private:
	GameObject* m_MainCamera = nullptr;
	GameObject* m_pPlayer = nullptr;

	bool m_bEnter = false;

	float	m_fEvasionTime = 0.f;
	float	m_fEvasiontScore = 0.f;
};

