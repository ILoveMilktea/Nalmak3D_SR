#pragma once
#include "IState.h"
class PlayerTopViewMove :
	public IState
{
	//ź������ ����ؾ��Ұ�
	//-> �̻��ϰ��� ���� y�ຯȭ�� �ִµ� �浹ó���� ��°�� �ҷ���?
	//��� ������Ʈ���� y���� 0���� ���� �غ�����?
		//->���Ű����Ű��⵵ �ϱ�
public:
	PlayerTopViewMove();
	virtual ~PlayerTopViewMove();

	// IState��(��) ���� ��ӵ�
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

