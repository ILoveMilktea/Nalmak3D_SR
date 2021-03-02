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
	bool EnterProduce();
	
	const Vector3& RandForShaking();
	void CameraShaking();
	void BossAppear();


private:
	float	m_fBossTime = 0.f;
	float	m_fBossScore = 0.f;
	bool	m_bEnter = false;

	GameObject*	m_pPlayer = nullptr;
	GameObject*	m_pMainCamera = nullptr;
	GameObject* m_pBoss = nullptr;

	//1. player move to certain pos + rotate reset
	bool	m_bPlayerSetting = true;
	Vector3		m_vPlayerInitPos = { 0, 0, 0 };

	//2. camera shaking
	bool	m_bCameraShaking = false;
	Vector3 vCameraOrigin = {0,0,0};
	Vector3 vCameraRand = { 0,0,0 };
	float	fShakingTime = 10.f;
	float	fShakingForce = 0.3f;

	//3. Boss Move + Player Move
	bool	m_bBossMove = false;
	bool	m_bPlayerMove = false;
	
	//4. Camera Produce
	bool	m_bCameraProduce = false;

};

