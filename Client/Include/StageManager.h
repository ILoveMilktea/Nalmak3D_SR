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

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
private:
	StateControl* m_stateControl;
};

