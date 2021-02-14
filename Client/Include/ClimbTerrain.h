#pragma once
#include "Component.h"
class ClimbTerrain :
	public Component
{
public:
	struct Desc
	{
		Terrain* terrain;
	};
public:
	ClimbTerrain(Desc* _desc);
	~ClimbTerrain();
private:
	Terrain* m_targetTerrain;

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
};

