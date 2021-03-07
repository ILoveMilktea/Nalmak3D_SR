#pragma once
#include "IState.h"
class DogFight_Stage1 :
	public IState
{
public:
	DogFight_Stage1();
	virtual ~DogFight_Stage1();

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

	void Player_Faraway();
	void Accelerate();

private:
	GameObject* m_Player = nullptr;
	Camera* m_pMainCamera = nullptr;


	Vector3 vPlayerOrigin;
	bool	m_bSceneChange = false;
	float	m_fSpd = 0.f;

							//생성	//클리어
	bool	m_bPattern1[2] = { false, false };
	bool	m_bPattern2[2] = { false, false };
	bool	m_bPattern3[2] = { false, false };

	float	m_fTutorialTime = 0.f;
	float	m_fTutorialScore = 0.f;

	int		m_iFrame = 0;
	float	m_fProduceDelta = 0.f;
};

