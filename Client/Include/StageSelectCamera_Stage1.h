#pragma once
#include "IState.h"
class StageSelectCamera_Stage1 :
	public IState
{
public:
	StageSelectCamera_Stage1();
	~StageSelectCamera_Stage1();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	class StageSelectCamera* m_stageCam;
	Vector3 m_stage1_position;
};

