#pragma once
#include "IState.h"

class DogFight_Stage1_3 :
	public IState
{
public:
	DogFight_Stage1_3();
	virtual ~DogFight_Stage1_3();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:

private:	
	Camera*			m_pMainCam = nullptr;
	GameObject*		m_pPlayer = nullptr;
	GameObject*		m_pScripter = nullptr;
	class StageManager*	m_pStageMgr = nullptr;

};

