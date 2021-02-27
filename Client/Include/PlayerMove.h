#pragma once
#include "IState.h"
class PlayerMove :
	public IState
{
public:
	PlayerMove();
	virtual ~PlayerMove();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;


	void TemproryAttackFunc(); 
	Quaternion* Rotation(const Vector3& _dir);
	//Vector3 Move(const int& _dirPara = 0);
private:
	InputManager* m_inputManager;
	TimeManager*  m_timeMananger;
	class PlayerInfoManager* m_playerInfo;
	class MouseOption* m_mouse;
	float m_accel = 0;
	class UseItem* m_useItem;


};

