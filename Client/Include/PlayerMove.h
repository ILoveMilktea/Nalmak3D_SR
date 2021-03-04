#pragma once
#include "IState.h"
class PlayerMove :
	public IState
{
public:
	PlayerMove();
	virtual ~PlayerMove();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;


	Quaternion* Rotation(const Vector3& _dir);
	//Vector3 Move(const int& _dirPara = 0);
private:
	InputManager* m_inputManager;
	TimeManager*  m_timeMananger;
	class PlayerInfoManager* m_playerInfo;
	float m_accel = 0;

	float m_rotZAngle = 0;
	float m_rotXAngle = 0;
	float m_rotYAngle = 0;


public:
	float GetRotXAngle();
	float GetRotYAngle();
	float GetRotZAngle();


};

