#pragma once
#include "Component.h"
class StageManager :
	public Component
{
private:
	static StageManager* m_instance;
public:
	static StageManager* GetInstance();
	static void DeleteInstance();

public:
	struct Desc
	{

	};
public:
	StageManager(Desc* _desc);
	~StageManager();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

public:
	void ToEvasion();
	void ToBoss();
	void ToScene(const wstring& _sceneName);

private:
	StateControl* m_stateControl;
};

