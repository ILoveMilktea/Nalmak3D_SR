#pragma once
#include "IState.h"
class GarageSceneCameraIntro :
	public IState
{
public:
	GarageSceneCameraIntro();
	~GarageSceneCameraIntro();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	Transform* m_player;
	class GarageSceneCameraInfo* m_garageCam;
};

