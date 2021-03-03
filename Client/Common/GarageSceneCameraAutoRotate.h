#pragma once
#include "IState.h"
class GarageSceneCameraAutoRotate :
	public IState
{
public:
	GarageSceneCameraAutoRotate();
	~GarageSceneCameraAutoRotate();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	class GarageSceneCameraInfo* m_garageCam;
};

