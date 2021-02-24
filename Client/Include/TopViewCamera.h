#pragma once

#include "Component.h"

class TopViewCamera :
	public Component
{
public:
	struct Desc
	{
			
	};
public:
	TopViewCamera(Desc* _desc);
	virtual ~TopViewCamera();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

public:

public:

private:
	GameObject* m_MainCamera = nullptr;

};

