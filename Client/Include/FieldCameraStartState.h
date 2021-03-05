#pragma once
#include "IState.h"
class FieldCameraStartState :
	public IState
{
public:
	FieldCameraStartState();
	virtual ~FieldCameraStartState();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	class GarageSceneCameraInfo* m_FieldCam;

};

