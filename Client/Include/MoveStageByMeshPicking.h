#pragma once
#include "Component.h"
class MoveStageByMeshPicking :
	public Component
{
public:
	struct Desc
	{
		wstring targetStage;
	};
public:
	MoveStageByMeshPicking(Desc* _desc);
	~MoveStageByMeshPicking();

public:
	virtual void Initialize() override;
	virtual void Update() override;

private:
	MeshPicking* m_meshPicking;
	wstring m_targetScene;
};

