#pragma once
#include "IState.h"
class GarageSceneCameraAutoRotate :
	public IState
{
public:
	GarageSceneCameraAutoRotate();
	~GarageSceneCameraAutoRotate();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	Transform* m_player;
	class GarageSceneCameraInfo* m_garageCam;


};

