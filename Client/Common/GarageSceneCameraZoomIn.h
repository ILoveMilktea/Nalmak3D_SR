#pragma once
#include "IState.h"
class GarageSceneCameraZoomIn :
	public IState
{
public:
	GarageSceneCameraZoomIn();
	~GarageSceneCameraZoomIn();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	class GarageSceneCameraInfo* m_garageCam;
};

