#pragma once
#include "Component.h"
class Camera_ActionManager :
	public Component
{

public:
	struct Desc
	{

	};
public:
	Camera_ActionManager(Desc* _desc);
	virtual ~Camera_ActionManager();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

public:
	static Camera_ActionManager* GetInstance();
	static void DeleteInstance();

private:
	static Camera_ActionManager * m_instance;
private:
	StateControl * m_camState;
};

