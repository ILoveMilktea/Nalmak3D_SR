#pragma once
#include "IState.h"
class DogFight_Stage2_1: public IState
{
public:
	DogFight_Stage2_1();
	~DogFight_Stage2_1();

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
	//void SceneToEvasion();

	//void Player_Faraway();
	//void Accelerate();

private:
	GameObject* m_pPlayer = nullptr;
	GameObject* m_pBoss = nullptr;
	Camera* m_pMainCamera = nullptr;


	//Vector3 vPlayerOrigin;

	bool	m_bNextPhase = false;
	bool	m_bProduce = false;
	float	m_fProduceDelta = 0.f;
							//생성	//클리어
	bool	m_bPattern1[2] = { false, false };
	bool	m_bPattern2[2] = { false, false };
	bool	m_bPattern3[2] = { false, false };
	

	float	m_fDogFightTime = 0.f;
	float	m_fDogFightScore = 0.f;

	int		m_iFrame = 0;
};
