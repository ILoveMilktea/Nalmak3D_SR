#pragma once
#include "Component.h"
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

public:
	static UIManager* GetInstance();
	static void DeleteInstance();

private:
	static UIManager* m_Instance;
};

