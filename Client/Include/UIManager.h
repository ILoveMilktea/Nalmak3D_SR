#pragma once
#include "Component.h"
class UI_Alarm;
class UIManager :
	public Component
{
public:
	struct Desc
	{

	};
public:
	UIManager(Desc* _desc);
	virtual ~UIManager();

private:
	virtual void Initialize() override;
	virtual void Update() override;

public:
	void SkillRotateOn(int _weaponIndex);
	void SkillRotate();
	bool SkillSingleRotate(bool _inverse, int _speed);
	void SetSkillRotatePivot(GameObject* _pivot) { m_skillRotatePivot = _pivot; }
private:
	GameObject* m_skillRotatePivot = nullptr;
	bool m_isSkillRotate	= false;
	bool m_isInverseRotate	= false;
	int m_curSkillIndex		= 0;
	int m_nextSkillIndex	= 0;
	int m_targetSkillIndex	= 0;
	float m_rotateTimer		= 0.f;
	float m_nextAngle		= 0.f;

	//=====================
	// alarm
public:
	void AddAlarm(UI_Alarm* _alarm);
	void UpdateAlarm();
	void RemoveAlarm();

private:
	vector<UI_Alarm*> m_messenger;
	queue<UI_Alarm*> m_alarmQueue;
	queue<UI_Alarm*> m_trashbag;

	float m_alarmTimer;

public:
	static UIManager* GetInstance();
	static void DeleteInstance();

private:
	static UIManager* m_Instance;

	//===========================
	// shop 

public:
	void SetShopItemModel(GameObject* _model) { m_model = _model; }
	void SetCurrentSelectItem(const wstring& _name) { m_itemName = _name; }

	GameObject* GetShopItemModel() { return m_model; }
	const wstring&  GetCurrentSelectItem() { return m_itemName; }

private:
	GameObject* m_model;

	wstring m_itemName;
};

