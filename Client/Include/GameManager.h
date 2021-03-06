#pragma once
#include "Component.h"
class GameManager :
	public Component
{

private:
	static GameManager* m_instance;
public:
	static GameManager* GetInstance();
	static void DeleteInstance();

	struct Desc
	{


	};

public:
	GameManager(Desc* _desc);
	virtual ~GameManager();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;

	

public: /* Get */
	bool Get_StageClear(int _i) const;


public: /* Set */
	void Set_StageClear(int _i);

private:
	bool			m_bStageClear[2] = { false, false };
};

