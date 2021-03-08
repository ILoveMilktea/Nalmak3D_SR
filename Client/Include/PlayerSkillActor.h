#pragma once
#include "Component.h"
class PlayerSkillActor :
	public Component
{
public:
	struct Desc
	{

	};

public:
	PlayerSkillActor(Desc* _Desc);
	virtual ~PlayerSkillActor();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	void FirstStart();

	bool EquipSkill(PARTS_NUM _partsType);
	class PlayerItem*& GetSkillInfo() {return m_skillInfo;}
private:
	//class PlayerItem* m_playerSkill;
private:
	PlayerInfoManager* m_playerMgr;
	InputManager* m_inputMgr;
	Core * m_core;

private:
	StateControl* m_stateControl;

	bool m_cheat =false;

private:
	class PlayerItem* m_skillInfo;
};

