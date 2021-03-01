#pragma once
#include "Component.h"


struct StageInfo
{
	wstring stageName;

	wstring stageInfo;

	Vector3 stagePosition;

	bool isOpen = false;
};


class StageSelectSceneManager :
	public Component
{
private:
	static StageSelectSceneManager* m_instance;
public:
	static StageSelectSceneManager* GetInstance();
	static void DeleteInstance();
public:
	struct Desc
	{

	};
public:
	StageSelectSceneManager(Desc* _desc);
	~StageSelectSceneManager();

private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

public:
	const StageInfo& GetStageInfo(int _index);
	bool SelectStage(int _index);
	int GetSelectedStageIndex() { return m_currentSelectStageIndex; }
private:
	int m_currentSelectStageIndex;
	vector<StageInfo> m_stageList;
};

