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

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;


	bool EquipSkill(PARTS_NUM _partsType);
	class PlayerItem*& GetSkillInfo() {return m_skillInfo;}
private:
	//class PlayerItem* m_playerSkill;
private:
	class PlayerInfoManager* m_playerMgr;
	InputManager* m_inputMgr;

private:
	StateControl* m_stateControl;

private:
	class PlayerItem* m_skillInfo;
};

