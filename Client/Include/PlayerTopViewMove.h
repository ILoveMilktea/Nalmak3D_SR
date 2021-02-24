#pragma once
#include "IState.h"
class PlayerTopViewMove :
	public IState
{
	//탄막에서 고려해야할거
	//-> 미사일같은 경우는 y축변화가 있는데 충돌처리를 우째야 할려나?
	//모든 오브젝트들의 y축을 0으로 고정 해보리기?
		//->병신같을거같기도 하구
public:
	PlayerTopViewMove();
	virtual ~PlayerTopViewMove();

	// IState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

public:

public:
	void TopViewMoving();
	void Shooting();
	void Lean(int _a);
	//void Defend_Skill();

private:
	float m_fRotz = 0.f;

};

