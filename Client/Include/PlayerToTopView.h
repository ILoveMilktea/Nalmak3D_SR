#pragma once
#include "Component.h"

//�����

class PlayerToTopView :
	public Component
{
public:
	struct Desc
	{
	
	};

public:
	PlayerToTopView(Desc* _desc);
	virtual ~PlayerToTopView();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;

public:


public:
	void Player_Far();

	void Create_Fade();
	void Accelerate();

	bool Fade_In();
	bool Fade_Out();

private:
	bool		m_bProduce = false;
	GameObject*	m_Player = nullptr;
	GameObject*	m_Fade = nullptr;
	float		m_fSpd = 0.f;

};

