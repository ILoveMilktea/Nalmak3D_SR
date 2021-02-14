#pragma once
#include "Component.h"
class NextSceneLoad :
	public Component
{
public:
	struct Desc
	{

	};
public:
	NextSceneLoad(Desc* _desc);
	~NextSceneLoad();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
};

