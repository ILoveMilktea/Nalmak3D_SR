#pragma once
#include "Component.h"

//ø¨√‚øÎ
//π‰ π¨∞Ì ∞¢ Stateø°º≠ ª©¡÷±‚.

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

	// Component¿ª(∏¶) ≈Î«ÿ ªÛº”µ 
	virtual void Initialize() override;
	virtual void Update() override;

public:


public:
	void Player_Far();
	void Accelerate();
	void Create_Fade();
	

	bool Fade_In();
	bool Fade_Out();

private:
	bool		m_bProduce = false;
	GameObject*	m_Player = nullptr;
	GameObject* m_MainCamera = nullptr;
	GameObject*	m_Fade = nullptr;
	float		m_fSpd = 0.f;


	Vector3 PosTemp;
	Quaternion RotTemp;
	Vector3 PosTemp_camera;
	Quaternion RotTemp_camera;

};

